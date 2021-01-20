<template>
  <div class="home">
    <b-button @click="signOut">Sign Out</b-button>
    <div class="tanks">
      <div class="tank column is-6-desktop is-12-mobile">
        <div class="columns is-mobile">
          <div class="column is-6">
            <div class="card">
              <div class="card-content">
                <p>Temperature: {{ doc.data.temperature }}°C</p>
              </div>
            </div>
          </div>
          <div class="column is-6">
            <div class="card">
              <div class="card-content">
                <b-button @click="toggle(!doc.controls.filterEnabled, 'filterEnabled')">
                  {{ doc.controls.filterEnabled ? 'ON' : 'OFF'}}
                </b-button>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import firebase from 'firebase';
import BButton from 'buefy/src/components/button/Button';

export default {
  data() {
    return {
      user: {},
      doc: {},
    };
  },
  components: {
    BButton,
  },
  methods: {
    signOut() {
      firebase.auth().signOut().then(
        () => {
          this.$router.push('/sign-in');
        },
      );
    },
    toggle(state, controls) {
      firebase.firestore()
        .doc('tanks/5pDz0ra1U694gHJgQTWX')
        .update(`controls.${controls}`, state);
    },
  },
  mounted() {
    firebase.auth().onAuthStateChanged((user) => {
      if (user) {
        firebase
          .firestore()
          .doc('tanks/5pDz0ra1U694gHJgQTWX')
          .onSnapshot((doc) => {
            this.user = user;
            this.doc = doc.data();
          });
      }
    });
  },
};
</script>


<style lang="scss" scoped>
.tanks {
  display: flex;
}
.card {
  text-align: center;
}
</style>
