import {
  GET_USERID
} from './mutation-types'

import {
  GetUserID
} from '../service/getData.js'
export default {
  async [GET_USERID]({commit}) {
    let res = await GetUserID();
    commit(GET_USERID, res)
  }
}