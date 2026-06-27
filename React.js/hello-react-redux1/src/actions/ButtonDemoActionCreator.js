import Constant from '../Constant'

const ButtonDemoActionCreator = {
    clickButton(string) {
        return {type: Constant.CLICKED, payload: {value: string}}
    }
}

export default ButtonDemoActionCreator