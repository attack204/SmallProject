<template>
  <div>
    <button @click="SetUserInfo()">click here</button>
    <div>{{userInfo == null ? "null" : userInfo}}</div>
    <div>{{userId}}</div>
    <div>{{userMoney1}}</div>
    <div>{{userMoney2}}</div>
  </div>
</template>

<script>
import { mapActions, mapMutations } from 'vuex';
import { mapState } from 'vuex';


export default {
  methods: {
    ...mapMutations([
      'RECORD_USERINFO', 'RECORD_USERMONEY'
    ]),
    ...mapActions([
      'GET_USERID'
    ]),
    SetUserInfo() {
      let res = {
        username: "attack204",
        password: "123456",
      }
      this.RECORD_USERINFO(res)
    }
  },
  mounted() {
    this.RECORD_USERMONEY({money1: "233", money2: "456"})
    this.GET_USERID();
  },
  computed: {
    ...mapState([
      'userInfo', 'userMoney1', 'userMoney2', 'userId'
    ])    
  },
}
</script>

<style scoped>

</style>