import React, { Component } from 'react'
import Main from './Main'
import Header from './Header'

class App extends Component {
    render() {
        return (
            <div className="container">
                <Header />
                <hr />
                <Main />
            </div>
        )
    }
}

export default App