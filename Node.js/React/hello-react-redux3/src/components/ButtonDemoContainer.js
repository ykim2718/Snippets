import { connect } from 'react-redux'
import ButtonDemo from './ButtonDemo'
import ButtonDemoActionCreator from '../actions/ButtonDemoActionCreator'

const mapStateToProps = (state) => {
    return {
        message: state.ButtonDemo.message,
    }
}

const mapDispatchToProps = (dispatch) => {
    return {
        dispatchClickButton: (name) => dispatch(ButtonDemoActionCreator.clickButton(name)),
    }
}

const ButtonDemoContainer = connect(mapStateToProps, mapDispatchToProps)(ButtonDemo)
export default ButtonDemoContainer

