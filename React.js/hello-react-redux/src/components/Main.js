import React from 'react'
import { renderRoutes } from 'react-router-config'
import { routes } from '../routes'

class Main extends React.Component {
    render() {
        return (
            renderRoutes(routes)
        )
    }
}

export default Main