/*
 * Create unnamed portal to run the query or queries in. If there
 * already is one, silently drop it.
 */
portal = CreatePortal("", true, true);
/* Don't display the portal in pg_cursors */
portal->visible = false;
if (HYBRID_MESSAGE != messageType) {
if (is_multistmt && (IsConnFromApp() || IsConnFromInternalTool())) {
//***
} else
PortalDefineQuery(portal, NULL, query_string, commandTag, plantree_list, NULL);
} else {
//***
}

/*
 * Start the portal.  No parameters here.
 */
PortalStart(portal, NULL, 0, InvalidSnapshot);

/*
 * Select the appropriate output format: text unless we are doing a
 * FETCH from a binary cursor.  (Pretty grotty to have to do this here
 * --- but it avoids grottiness in other places.  Ah, the joys of
 * backward compatibility...)
 */
format = 0; /* TEXT is default */
if (IsA(parsetree, FetchStmt)) {
FetchStmt* stmt = (FetchStmt*)parsetree;

if (!stmt->ismove) {
Portal fportal = GetPortalByName(stmt->portalname);

if (PortalIsValid(fportal) && ((uint32)fportal->cursorOptions & CURSOR_OPT_BINARY))
format = 1; /* BINARY */
}
}
PortalSetResultFormat(portal, 1, &format);
/*
 * Now we can create the destination receiver object.
 */
receiver = CreateDestReceiver(dest);
if (dest == DestRemote)
SetRemoteDestReceiverParams(receiver, portal);


//执行器真正开始
/*
 * Run the portal to completion, and then drop it (and the receiver).
 */
(void)PortalRun(portal, FETCH_ALL, isTopLevel, receiver, receiver, completionTag);

(*receiver->rDestroy)(receiver);

PortalDrop(portal, false);


CleanHotkeyCandidates(true);

/* restore is_allow_commit_rollback */
if (is_compl_sql) {
stp_reset_xact_state_and_err_msg(savedisAllowCommitRollback, needResetErrMsg);
}
if (IsA(parsetree, TransactionStmt)) {
/*
 * If this was a transaction control statement, commit it. We will
 * start a new xact command for the next command (if any).
 */
finish_xact_command();
} else if (lnext(parsetree_item) == NULL) {
/*
 * If this is the last parsetree of the query string, close down
 * transaction statement before reporting command-complete.  This
 * is so that any end-of-transaction errors are reported before
 * the command-complete message is issued, to avoid confusing
 * clients who will expect either a command-complete message or an
 * error, not one and then the other.  But for compatibility with
 * historical openGauss behavior, we do not force a transaction
 * boundary between queries appearing in a single query string.
 */
finish_xact_command();
} else {
/*
 * We need a CommandCounterIncrement after every query, except
 * those that start or end a transaction block.
 */
CommandCounterIncrement();
}
/*
 * Tell client that we're done with this query.  Note we emit exactly
 * one EndCommand report for each raw parsetree, thus one for each SQL
 * command the client sent, regardless of rewriting. (But a command
 * aborted by error will not send an EndCommand report at all.)
 */
EndCommand(completionTag, dest);
}
/*
* Close down transaction statement, if one is open.
*/
finish_xact_command();