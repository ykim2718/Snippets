import Home from './components/Home'
import About from './components/About'
import NotFound from './components/NotFound'
import ButtonDemoContainer from './components/ButtonDemoContainer'
import ListDemoContainer from './components/ListDemoContainer'

const routes = [
    { path: '/', exact: true, component: Home},
    { path: '/about', exact: true, component: About},
    { path: '/button', exact: true, component: ButtonDemoContainer},
    { path: '/list', exact: true, component: ListDemoContainer},
    { path: '*', exact: true, component: NotFound},
    // table
    // icon
    // d3 chart
    // db access
    // spread sheet: 'react as-grid'
]

export { routes }