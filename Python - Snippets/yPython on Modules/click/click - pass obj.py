"""
y, 2022.2.25
click - pass obj.py
https://click.palletsprojects.com/en/8.0.x/advanced/?highlight=ctx%20obj
"""

import click
import os


class Repo:
    def __init__(self, home=None):
        self.home = os.path.abspath(home or ".")
        self.db = None

    def __enter__(self):
        path = os.path.join(self.home, "repo.db")
        self.db = open_database(path)

    def __exit__(self, exc_type, exc_value, tb):
        self.db.close()


@click.group()
@click.option("--repo-home", default=".repo")
@click.pass_context
def cli(ctx, repo_home):
    ctx.obj = ctx.with_resource(Repo(repo_home))


@cli.command()
@click.pass_obj
def log(obj):
    # obj is the repo opened in the cli group
    for entry in obj.db.query(...):
        click.echo(entry)


cli()
