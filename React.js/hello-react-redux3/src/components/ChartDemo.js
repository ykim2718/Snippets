/*
https://material-ui.com/layout/grid/
*/

import React from 'react';
import PropTypes from 'prop-types';
import { withStyles } from '@material-ui/core/styles';
import Grid from '@material-ui/core/Grid';
import Paper from '@material-ui/core/Paper';
import SimpleLineChart from './charts/SimpleLineChart'
import BiaxialLineChart from './charts/BiaxialLineChart'
import JointLineScatterChart from './charts/JointLineScatterChart'
import ThreeDimScatterChart from './charts/ThreeDimScatterChart'
import PositiveAndNegativeBarChart from './charts/PositiveAndNegativeBarChart'
import MultipleYAxesScatterChart from './charts/MultipleYAxesScatterChart'
import TwoLevelPieChart from './charts/TwoLevelPieChart'

const chartLists = [
    {name: 'SimpleLineChart', chart: (<SimpleLineChart />)},
    {name: 'BiaxialLineChart', chart: (<BiaxialLineChart />)},
    {name: 'JointLineScatterChart', chart: (<JointLineScatterChart />)},
    {name: 'ThreeDimScatterChart', chart: (<ThreeDimScatterChart />)},
    {name: 'PositiveAndNegativeBarChart', chart: (<PositiveAndNegativeBarChart />)},
    {name: 'MultipleYAxesScatterChart', chart: (<MultipleYAxesScatterChart />)},
    {name: 'TwoLevelPieChart', chart: (<TwoLevelPieChart />)},
]

const styles = theme => ({
    paper: {
        height: 400,
        width: '100%',
        // padding: theme.spacing.unit * 2,
    },
});
const gridContainerStyles = {
    spacing: '16',
    align: "center",
    // justify: "center",
}
const gridItemStyles = {
    xs: 6,
}

class ChartDemoGrid extends React.Component {
    render() {
        const { classes } = this.props;
        return (
            <Grid container {...gridContainerStyles}>
                {chartLists.map((value, j) => (
                    <Grid item key={j} {...gridItemStyles}>
                        <Paper>
                            {value.name}
                            {value.chart}
                        </Paper>
                    </Grid>
                ))}
            </Grid>
        )
    }
}

ChartDemoGrid.propTypes = {
    classes: PropTypes.object.isRequired,
}

export default withStyles(styles)(ChartDemoGrid)