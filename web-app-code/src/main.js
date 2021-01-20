import Vue from 'vue';
import Buefy from 'buefy';
import firebase from 'firebase';
import App from '@/App.vue';
import router from '@/router';
import '@/registerServiceWorker';
import 'buefy/dist/buefy.css';
import 'bulma-helpers/css/bulma-helpers.min.css';

Vue.config.productionTip = false;
Vue.use(Buefy);

const firebaseConfig = {
  apiKey: 'AIzaSyBrqMObXKSIfeZvwGex4oIh0K1wkFJGaEU',
  authDomain: 'pervasive-software-engineering.firebaseapp.com',
  databaseURL: 'https://pervasive-software-engineering-default-rtdb.firebaseio.com',
  projectId: 'pervasive-software-engineering',
  storageBucket: 'pervasive-software-engineering.appspot.com',
  messagingSenderId: '947713545557',
  appId: '1:947713545557:web:ced390e79a24af6d970bdc',
  measurementId: 'G-PDF0WLBMC1',
};

firebase.initializeApp(firebaseConfig);

let app = '';

firebase.auth().onAuthStateChanged(() => {
  if (!app) {
    app = new Vue({
      router,
      render: h => h(App),
    }).$mount('#app');
  }
});
