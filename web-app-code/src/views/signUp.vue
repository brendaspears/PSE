<template>
  <div class="sign-up">
    <div class="container">
      <div class="section">
        <div class="columns">
          <div class="column is-4 is-offset-4">
            <b-field label="Email">
              <b-input placeholder="Email" v-model="email"/>
            </b-field>
            <b-field label="Password">
              <b-input
                placeholder="Password"
                type="password"
                v-model="password"
                @keyup.native.enter="signUp"
              />
            </b-field>
            <div class="has-text-centered">
              <b-button
                type="is-success"
                @click="signUp"
                :loading="loading"
              >
                Sign Up
              </b-button>
            </div>
            <div class="has-text-centered">
              <router-link
                :to="{
                  name: 'signIn'
                }"
                class="button is-text is-size-7 has-margin-top-10"
              >
                Click here to sign in
              </router-link>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import firebase from 'firebase';

export default {
  name: 'signUp',
  data() {
    return {
      email: '',
      password: '',
      loading: false,
    };
  },
  methods: {
    signUp() {
      this.loading = true;
      firebase.auth().createUserWithEmailAndPassword(this.email, this.password).then(
        () => {
          this.loading = false;
          this.$router.replace('sign-in');
          this.$buefy.toast.open({
            message: 'User successfully created',
            type: 'is-success',
            position: 'is-top',
          });
        },
        (err) => {
          this.loading = false;
          this.$buefy.toast.open({
            message: err.message,
            type: 'is-danger',
            position: 'is-top',
          });
        },
      );
    },
  },
};
</script>

<style lang="scss" scoped>
.sign-up {
  display: flex;
  align-items: center;
  justify-content: center;
  height: 100vh;
  width: 100vw;
}
</style>
