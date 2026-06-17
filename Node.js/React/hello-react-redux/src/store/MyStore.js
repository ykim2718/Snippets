import { createStore, applyMiddleware } from 'redux'
import reduxThunk from 'redux-thunk'  // enable the use of action function like action object, y, 2019.4.24
import RootReducer from '../reducers/RootReducer'

const MyStore = createStore(RootReducer, applyMiddleware(reduxThunk))
export default MyStore