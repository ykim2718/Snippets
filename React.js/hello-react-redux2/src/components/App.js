import React, { Component } from 'react'
import Main from './Main'
import Header from './Header'

class App extends Component {
    render() {
        console.log(this.props, document)
        return (
            <React.Fragment>
                <div className="container">
                    <Header />
                    <hr />
                    <Main />
                </div>
             
            </React.Fragment>
        )
    }
}

export default App