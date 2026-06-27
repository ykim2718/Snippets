import { createStore, applyMiddleWare } from 'redux'
// import reduxThunk from 'redux-thunk'
import ButtonDemoReducer from '../reducers/ButtonDemoReducer'

const MyStore = createStore(ButtonDemoReducer)
export default MyStore