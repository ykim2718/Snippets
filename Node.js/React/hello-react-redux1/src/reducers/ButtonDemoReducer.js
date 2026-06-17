import Constant from '../Constant'
import produce from 'immer'

const initialState = {
    message: "Hello React-Redux ^____^;;"
}

const ButtonReducer = (state=initialState, action) => {
    let newState
    switch (action.type) {
        case Constant.CLICKED:
            newState = produce(state, (draft) => { draft.message = action.payload.value })
            return newState
        default:
            return state
    }
}

export default ButtonReducer
