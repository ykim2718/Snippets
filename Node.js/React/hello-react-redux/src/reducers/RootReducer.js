import { combineReducers } from 'redux'
import ButtonDemoReducer  from './ButtonDemoReducer'
import ListDemoReducer  from './ListDemoReducer'

const RootReducer = combineReducers({
    ButtonDemo: ButtonDemoReducer,
    ListDemo: ListDemoReducer,
})

export default RootReducer
