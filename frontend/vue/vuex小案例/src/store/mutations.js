import {
  RECORD_USERINFO,
  RECORD_USERMONEY,
  GET_USERID,
} from './mutation-types.js'

export default {
  [RECORD_USERINFO](state, 
    info
  ) {
    state.userInfo = info;
  },
  [RECORD_USERMONEY](state, 
    {money1, money2}
  ) {
    state.userMoney1 = money1;
    state.userMoney2 = money2;
  },
  [GET_USERID](state, info) {
    state.userId = info;
  },
}