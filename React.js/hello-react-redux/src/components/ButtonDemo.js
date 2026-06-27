import React, { Component } from 'react'
import PropTypes from 'prop-types'
import { Dropdown, Card } from 'react-bootstrap'
import { GuardiansOfTheGalaxy as GAG } from '../MyDB'

let texts = Object.keys(GAG)

class ButtonDemo extends Component {
    handleClick = (j) => {
        this.props.dispatchClickButton(texts[j])
    }
    render() {
        console.log(this.props)
        return (
            <div>
                <div className="btn-group"> {texts.map((text, j) =>
                    <button type="button" className="btn btn-primary" style={{ backgroundColor: 'blue' }}
                        key={j} onClick={() => this.handleClick(j)}>{text}</button>
                )}
                </div>
                <div className="btn-group" style={{ marginLeft: '0.5em' }}>
                    <Dropdown>
                        <Dropdown.Toggle variant="success" id="dropdown-basic">Dropdown Button</Dropdown.Toggle>
                        <Dropdown.Menu>
                            <Dropdown.Item href="#action-1">Action</Dropdown.Item>
                            <Dropdown.Item href="#action-2">Another action</Dropdown.Item>
                            <Dropdown.Item href="#action-3">Something else</Dropdown.Item>
                        </Dropdown.Menu>
                    </Dropdown>
                </div>
                {this.props.message.actor &&
                    <Card style={{ width: '16rem' }} className='card d-block'>
                        <Card.Img variant="top" src={this.props.message.image} />
                        <Card.Body>
                            <Card.Title>{this.props.message.actor}</Card.Title>
                            <Card.Text>Gurdians of the Galaxy (2014)</Card.Text>
                        </Card.Body>
                    </Card>
                }
            </div>
        )
    }
}
// {this.props.message_actor && <p>{this.props.message_actor}</p>}

ButtonDemo.propTypes = {
    message: PropTypes.object.isRequired,
    dispatchClickButton: PropTypes.func.isRequired,
}

export default ButtonDemo