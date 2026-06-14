import Home from './components/Home'
import About from './components/About'
import NotFound from './components/NotFound'
import ButtonDemoContainer from './components/ButtonDemoContainer'
import ListDemoContainer from './components/ListDemoContainer'
import TableDemo from './components/TableDemo'
import ChartDemo from './components/ChartDemo'
import ControlDemo from './components/ControlDemo'
import DBDemo from './components/DBDemo'

const routes = [
    {path: '/', exact: true, component: Home},
    {path: '/about', exact: true, component: About},
    {path: '/button', exact: true, component: ButtonDemoContainer},
    {path: '/list', exact: true, component: ListDemoContainer},
    {path: '/table', exact: true, component: TableDemo},
    {path: '/chart', exact: true, component: ChartDemo},
    {path: '/control', exact: true, component: ControlDemo},
    {path: '/db', exact: true, component: DBDemo},
    {ath: '*', exact: true, component: NotFound},
]

export { routes }