import C from '../Constant'
import produce from 'immer'

const initialState = {
    message: {actor: "", image: ""}
}

const ButtonDemoReducer = (state=initialState, action) => {
    let newState
    switch (action.type) {
        case C.CLICKED:
            newState = produce(state, (draft) => {
                draft.message.actor = action.payload.actor
                draft.message.image = action.payload.image
            })
            return newState
        default:
            return state
    }
}

export default ButtonDemoReducer
