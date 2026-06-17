import React, { Component } from 'react'
import PropTypes from 'prop-types'
import { Dropdown } from 'react-bootstrap'

const texts = ['Peter Quill / Star-Lord', 'Gamora', 'Drax the Destroyer', 'Groot', 'Rocket']

class ButtonDemo extends Component {
    handleClick = (j) => {
        this.props.dispatchClickButton(texts[j])
    }

    render() {
        return (
            <div>
                <div className="btn-group"> {texts.map((text, j) => 
                    <button type="button" className="btn btn-primary" style={{ backgroundColor: 'blue'}}
                    key={j} onClick={() => this.handleClick(j)}>{text}</button>
                    )}
                </div>
                <div className="btn-group" style={{ marginLeft: '0.5em'}}>
                    <Dropdown>
                        <Dropdown.Toggle variant="success" id="dropdown-basic">Dropdown Button</Dropdown.Toggle>
                        <Dropdown.Menu>
                            <Dropdown.Item href="#action-1">Action</Dropdown.Item>
                            <Dropdown.Item href="#action-2">Another action</Dropdown.Item>
                            <Dropdown.Item href="#action-3">Something else</Dropdown.Item>
                        </Dropdown.Menu>
                    </Dropdown>
                </div>
                {this.props.message && <p>{this.props.message}</p>}
            </div>
        )
    }
}

ButtonDemo.propTypes = {
    message: PropTypes.string.isRequired,
    dispatchClickButton: PropTypes.func.isRequired,
}

export default ButtonDemo