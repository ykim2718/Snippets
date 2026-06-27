import React, { Component } from 'react'

const bodyFontStyle= {
    fontSize: '0.6em'
}

class Home extends Component {
    render() {
        return (
            <div>
                <h3>Y Gym/Playground for React-Redux</h3>
                <ul style={{fontSize: '24px', padding: '0'}}>
                    <li>button w/ react-bootstrap@1.x.x</li>
                        <div style={bodyFontStyle}>
                        ReactJS course from 4/1 to 4/5, 2019
                        </div>
                    <li>list + modal w/ react-bootstrap@1.x.x</li>
                        <div style={bodyFontStyle}>
                        https://getbootstrap.com/docs/4.0/components/modal/
                        </div>
                    <li>table w/ material-ui table</li>
                        <div style={bodyFontStyle}>
                        https://material-ui.com/demos/tables/
                        </div>
                    <li>control w/ materail-ui popover</li>
                        <div style={bodyFontStyle}>
                        https://material-ui.com/utils/popover/
                        </div>
                    <li>chart w/ recharts</li>
                        <div style={bodyFontStyle}>
                        http://recharts.org/en-US/
                        </div>
                    <li>db access via web server</li>
                    <li>spread sheet w/ react-virtualized</li>
                        <div style={bodyFontStyle}>
                        https://www.npmtrends.com/react-data-grid-vs-react-datasheet-vs-react-list-vs-react-table-vs-react-virtualized-vs-ag-grid<br/>
                        https://github.com/bvaughn/react-virtualized/blob/master/docs/Table.md<br/>
                        </div>
                    <li>svg</li>
                    <li>animation</li>
                </ul>
            </div>
        )
    }
}

export default Home