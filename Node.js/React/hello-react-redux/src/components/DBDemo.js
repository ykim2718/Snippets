import React, { Component } from 'react'
import PropTypes from 'prop-types'

class DBDemo extends Component {
    render() {
        return (
            <div>
                DBDemo.js
            </div>
        )
    }
}

DBDemo.propTypes = {
    message: PropTypes.string.isRequired,
    dispatchClickButton: PropTypes.func.isRequired,
}

export default DBDemo