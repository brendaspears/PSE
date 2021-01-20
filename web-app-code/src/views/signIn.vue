<template>
  <div class="sign-in">
    <div class="container">
      <div class="section">
        <div class="columns">
          <div class="column is-4 is-offset-4">
            <b-field label="Email">
              <b-input
                placeholder="Email"
                v-model="email"
              />
            </b-field>
            <b-field label="Password">
              <b-input
                placeholder="Password"
                type="password"
                v-model="password"
                @keyup.native.enter="signIn"
              />
            </b-field>
            <div class="has-text-centered">
              <b-button
                type="is-success"
                @click="signIn"
                :loading="loading"
                @keyup.native.enter="signIn"
              >
                Sign In
              </b-button>
            </div>
            <div class="has-text-centered">
              <router-link
                :to="{
                  name: 'signUp'
                }"
                class="button is-text is-size-7 has-margin-top-10"
              >
                Click here to sign up
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
  name: 'signIn',
  data() {
    return {
      email: '',
      password: '',
      loading: false,
    };
  },
  methods: {
    signIn() {
      this.loading = true;
      firebase.auth().signInWithEmailAndPassword(this.email, this.password).then(
        () => {
          this.loading = false;
          this.$router.replace('home');
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
.sign-in {
  display: flex;
  align-items: center;
  justify-content: center;
  height: 100vh;
  width: 100vw;
}
</style>
