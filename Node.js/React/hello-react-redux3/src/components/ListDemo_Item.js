import React from 'react'
import PropTypes from 'prop-types'
import { Container, Row, Col } from 'react-bootstrap'

class ListDemoItem extends React.Component {
    render() {
        return (
            <li>
                <div className="list-group-item">
                    <Container>
                        <Row>
                            <Col xs="auto">
                                <img src={this.props.image} alt={this.props.painting} className="thumbnail" style={{ width: "10em" }} />
                            </Col>
                            <Col xs="7">
                                <span>{this.props.artist}</span><br />
                                <span>{this.props.painting}</span><br />
                                <span>{this.props.medium}</span><br />
                                <span>{this.props.year}</span><br />
                                <span>{this.props.location}</span><br />
                                <div>{this.props.note}</div>
                            </Col>
                            <Col xs="2">
                                <button className="btn btn-primary btn-sm"
                                    onClick={() => this.props.deleteItem(this.props.no)}>Delete</button>
                                <div>isLoading={this.props.isLoading.toString()}</div>
                            </Col>
                        </Row>
                    </Container>
                </div>
            </li>
        )
    }
}

ListDemoItem.propTypes = {
    artist: PropTypes.string.isRequired,
    image: PropTypes.string.isRequired,
    painting: PropTypes.string.isRequired,
    year: PropTypes.number.isRequired,
    deleteItem: PropTypes.func.isRequired,
}

export default ListDemoItem