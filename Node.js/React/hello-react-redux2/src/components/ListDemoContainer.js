import { connect } from 'react-redux'
import ListDemo from './ListDemo'
import ListDemoActionCreator from '../actions/ListDemoActionCreator'

const mapStateToProps = (state) => {
    return {
        listItems: state.ListDemo.listItems,
        isLoading: state.ListDemo.isLoading,
    }
}

const mapDispatchToProps = (dispatch) => {
    return {
        dispatchIsLoading: (show) => dispatch(ListDemoActionCreator.getLoadingAction(show)),
        dispatchAddListItem: () => dispatch(ListDemoActionCreator.addListItem()),
        dispatchDelListItem: (j) => dispatch(ListDemoActionCreator.delListItem(j)),
    }
}

const ListDemoContainer = connect(mapStateToProps, mapDispatchToProps)(ListDemo)
export default ListDemoContainer

