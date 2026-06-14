import React, { Component } from 'react'
import PropTypes from 'prop-types'
import ListDemoItem from './ListDemo_Item'
import { Modal, Spinner, Button } from 'react-bootstrap'

class ListDemo extends Component {
    clickAddButton = () => {
        this.props.dispatchAddListItem()
    }
    clickDelButton = (j) => {
        this.props.dispatchDelListItem(j)
    }
    closeModalDialog = () => {
        this.props.dispatchIsLoading(false)
    }
    render() {
        let Items = this.props.listItems.map((item, j) => {
            return <ListDemoItem key={j} no={j} {...item} isLoading={this.props.isLoading}
                deleteItem={this.clickDelButton} />
        })
        return (
            <React.Fragment>
                <div className="btn-group" style={{ marginBottom: '0.5em' }}>
                    <button type="button" className="btn btn-primary" onClick={this.clickAddButton}>Add</button>
                </div>
                <ul className="list-group" style={{ listStyleType: 'none' }}>
                    {Items}
                </ul>
                <Modal
                    size="md" aria-labelledby="contained-modal-title-vcenter"
                    centered show={this.props.isLoading >= 1} onHide={() => { }}>
                    <Modal.Header>
                        <Modal.Title>Hang on a second <Spinner animation="grow" variant="success" />
                        </Modal.Title>
                    </Modal.Header>
                    <Modal.Body>Waiting for a some process with delay</Modal.Body>
                    {/* <Modal.Footer> </Modal.Footer> */}
                </Modal>
                <Modal
                    size="md" aria-labelledby="contained-modal-title-vcenter"
                    centered show={this.props.isLoading === -1} onHide={this.closeModalDialog}>
                    <Modal.Header closeButton>
                        <Modal.Title style={{ color: "red" }}>No more images left at the depot</Modal.Title>
                    </Modal.Header>
                    <Modal.Footer>
                        <Button onClick={this.closeModalDialog}>Close</Button>
                    </Modal.Footer>
                </Modal>
            </React.Fragment>
        )
    }
}

ListDemo.propTypes = {
    listItems: PropTypes.arrayOf(PropTypes.object).isRequired,
    dispatchAddListItem: PropTypes.func.isRequired,
    dispatchDelListItem: PropTypes.func.isRequired,
}

export default ListDemo