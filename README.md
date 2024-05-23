# rush01

from dash import Dash, html, dcc, callback, Output, Input
import plotly.express as px
import pandas as pd

# Inicialización de la aplicación
app = Dash(__name__)

# Cargar los datos
athletes = pd.read_csv("./data/athletes.csv", delimiter=",")
medals = pd.read_csv("./data/medals.csv", delimiter=",")

# Rellenar valores nulos en altura de atletas
athletes['height_m/ft'] = athletes['height_m/ft'].fillna(0)

# Conteo de atletas por país y género
athletes_per_country_gender = athletes.groupby(['country', 'gender']).size().reset_index(name='Number of Athletes')

# Conteo de medallas por país y género
medals['gender'] = medals['medal_type'].apply(lambda x: 'Female' if x.endswith('F') else 'Male')
medals_per_country_gender = medals.groupby(['country', 'gender']).size().reset_index(name='Number of Medals')

# Colocación de elementos
app.layout = html.Div([
    html.H1(children='Género y Medallas en los JJOO Tokio 2020'),
    html.Hr(),
    html.Div([
        dcc.Slider(
            id='athlete-slider',
            min=1,
            max=athletes_per_country_gender['Number of Athletes'].max(),
            value=10,
            marks={i: str(i) for i in range(1, athletes_per_country_gender['Number of Athletes'].max() + 1, 5)},
            step=1
        ),
        html.Div(id='slider-output-container')
    ]),
    dcc.Graph(id='gender-balance-graph'),
    dcc.Graph(id='medal-distribution-graph')
])

# Callback para actualizar el gráfico basado en el filtro
@callback(
    Output('slider-output-container', 'children'),
    Output('gender-balance-graph', 'figure'),
    Output('medal-distribution-graph', 'figure'),
    Input('athlete-slider', 'value')
)
def update_graph(selected_value):
    filtered_athletes = athletes_per_country_gender[athletes_per_country_gender['Number of Athletes'] >= selected_value]
    filtered_medals = medals_per_country_gender[medals_per_country_gender['country'].isin(filtered_athletes['country'].unique())]

    # Gráfico de equilibrio de género
    gender_balance_fig = px.bar(filtered_athletes, x='country', y='Number of Athletes', color='gender',
                                title='Equilibrio de Género por País',
                                labels={'country': 'País', 'Number of Athletes': 'Número de Atletas'},
                                hover_data={'Number of Athletes': True, 'gender': True})

    # Gráfico de distribución de medallas
    medal_distribution_fig = px.bar(filtered_medals, x='country', y='Number of Medals', color='gender',
                                    title='Distribución de Medallas por Género',
                                    labels={'country': 'País', 'Number of Medals': 'Número de Medallas'},
                                    hover_data={'Number of Medals': True, 'gender': True},
                                    barmode='stack')

    return f'Filtrando por países con al menos {selected_value} atletas', gender_balance_fig, medal_distribution_fig

# Para uso en un .py independiente
if __name__ == '__main__':
    app.run_server(debug=True)
