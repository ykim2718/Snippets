import React from 'react';
import ReactDOM from 'react-dom';
import { BrowserRouter as Router} from 'react-router-dom';
import { Provider} from 'react-redux';
import 'bootstrap/dist/css/bootstrap.css';
import App from './components/App';
import MyStore from './store/MyStore';

ReactDOM.render(
    <Provider store={MyStore}>
        <Router>
            <App/>
        </Router>
    </Provider>
    , document.getElementById('root')
    );

// If you want your app to work offline and load faster, you can change
// unregister() to register() below. Note this comes with some pitfalls.
// Learn more about service workers: https://bit.ly/CRA-PWA
// serviceWorker.unregister();
