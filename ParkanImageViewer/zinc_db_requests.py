import requests
from bs4 import BeautifulSoup


def get_response_by_zinc_id(zinc_id):
    return requests.get(rf'http://zinc.docking.org/substances/{zinc_id}/activities/').text


def get_soup(html_doc):
    return BeautifulSoup(html_doc, 'html.parser')


def stringify(content):
    if isinstance(content, str):
        return content

    return content.string


def to_strings_list(tag):
    return map(stringify, tag.contents)


def prettify_string(string):
    return ' '.join(string.split())


def get_pretty_string(tag):
    str_list = to_strings_list(tag)
    initial_string = ''.join(str_list)
    pretty_string = initial_string.replace('\n', '')
    pretty_string = prettify_string(pretty_string)
    return pretty_string


def print_first_column(soup):
    all_tr = soup.table.tbody.find_all('tr')
    first_column = [get_pretty_string(tr.find('td')) for tr in all_tr]
    for s in first_column:
        print(s)


print_first_column(get_soup(get_response_by_zinc_id('ZINC000043204048')))
