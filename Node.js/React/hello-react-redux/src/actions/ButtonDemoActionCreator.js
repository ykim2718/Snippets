import Constant from '../Constant'
import { GuardiansOfTheGalaxy as GAG } from '../MyDB'

const ButtonDemoActionCreator = {
    clickButton(name) {
        return {type: Constant.CLICKED, payload: {actor: name, image: GAG[name]}}
    }
}

export default ButtonDemoActionCreator