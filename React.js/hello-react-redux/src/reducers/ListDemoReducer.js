import C from '../Constant'
import produce from 'immer'

const initialState = {
    listItems: [],
    isLoading: false,
}

const ListDemoReducer = (state = initialState, action) => {
    switch (action.type) {
        case C.IS_LOADING:
            return produce(state, (draft) => { draft.isLoading = action.isLoading })
        case C.ADD_ITEM:
            return produce(state, (draft) => { draft.listItems = action.listItems })
        case C.DEL_ITEM:
            return produce(state, (draft) => { draft.listItems.splice(action.item_id, 1) })
        default:
            return state
    }
}

export default ListDemoReducer
