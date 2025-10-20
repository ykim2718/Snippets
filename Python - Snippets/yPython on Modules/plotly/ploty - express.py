"""
y, 2025.10.17
plotly - express.py
"""

import pandas as pd
import plotly.express as px

# Sample data
data = {
    'City': ['New York', 'Los Angeles', 'Chicago'],
    'Population': [8398748, 3990456, 2705994]
}
df = pd.DataFrame(data)

# Create an interactive bar chart
fig = px.bar(df, x='City', y='Population', title='Population of Major Cities')

# Save the chart as a complete HTML file
fig.write_html('plotly - express.html', include_plotlyjs='cdn')
