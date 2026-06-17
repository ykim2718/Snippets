import Home from './components/Home'
import About from './components/About'
import NotFound from './components/NotFound'
import ButtonDemoContainer from './components/ButtonDemoContainer'

const routes = [
    { path: '/', exact: true, component: Home},
    { path: '/about', exact: true, component: About},
    { path: '/button', exact: true, component: ButtonDemoContainer},
    { path: '*', exact: true, component: NotFound},
]

export { routes }