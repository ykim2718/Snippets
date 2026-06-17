import React, { Component } from 'react'
// import { Link } from 'react-router-dom'

class Header extends Component {
    render() {
        return (
            <div>
                <h2 className="text-center">Hello React-Redux, April 2019</h2>
                <ul className="pagination">
                    <li className="page-item"><a className="page-link" href="/">Home</a></li>
                    <li className="page-item"><a className="page-link" href="/button">Button</a></li>
                    <li className="page-item"><a className="page-link" href="/about">About</a></li>
                </ul>
            </div>
        )
    }
}

export default Header