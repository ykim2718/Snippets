import C from '../Constant'
import produce from 'immer'

const initialState = {
    message: ""
}

const ButtonDemoReducer = (state=initialState, action) => {
    let newState
    switch (action.type) {
        case C.CLICKED:
            newState = produce(state, (draft) => { draft.message = action.payload.value })
            return newState
        default:
            return state
    }
}

export default ButtonDemoReducer
