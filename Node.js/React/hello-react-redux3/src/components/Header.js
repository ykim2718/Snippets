import React, { Component } from 'react'
import { Link } from 'react-router-dom'

class Header extends Component {
    render() {
        return (
            <div>
                <h1 className="text-center">Hello React-Redux, April 2019</h1>
                <ul className="pagination">
                    <li className="page-item"><Link className="page-link" to="/">Home</Link></li>
                    <li className="page-item"><Link className="page-link" to="/button">Button</Link></li>
                    <li className="page-item"><Link className="page-link" to="/list">List</Link></li>
                    <li className="page-item"><Link className="page-link" to="/table">Table</Link></li>
                    <li className="page-item"><Link className="page-link" to="/chart">Chart</Link></li>
                    <li className="page-item"><Link className="page-link" to="/control">Control</Link></li>
                    <li className="page-item"><Link className="page-link" to="/db">DB</Link></li>
                    <li className="page-item"><Link className="page-link" to="/about">About</Link></li>
                </ul>
            </div>
        )
    }
}

export default Header