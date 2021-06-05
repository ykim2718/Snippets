"""
y, pymongo - logger.py, 2018.8.4 - 5
http://www.hanbit.co.kr/channel/category/category_view.html?cms_code=CMS4250329609
https://docs.mongodb.com/manual/core/document/
"""

import logging
import pymongo
import sys


class YMongoHandler(logging.StreamHandler):
    """ y, 2018.8.4 """

    collection = None
    document = None
    save_as = 'document'  # or field_value; MongoDB documents are composed of field-and-value pairs.
    count = 0

    def __init__(self, database='test_database', collection='log', host='localhost', port=None,
                 save_as='field_value', command=None, **kwargs):

        assert save_as in ['document', 'element', 'field_value']

        super().__init__(**kwargs)

        self.collection = pymongo.MongoClient(host, port)[database][collection]
        try:
            self.collection.find_one()
        except:
            raise ConnectionError(r'cannot access MongoDB:\\{h}:{p}'.format(h=host, p=port if port else 27017))
            sys.exit(1)

        self.save_as = save_as
        if save_as in ['element', 'field_value']:
            doc = {
                'command': command,
                'log_counts': {
                    'debug': 0,
                    'info': 0,
                    'warning': 0,
                    'error': 0,
                    'critical': 0,
                    'else': 0,
                    'total': 0
                }
            }
            self.document = self.collection.insert_one(doc).inserted_id

    def emit(self, record):

        if self.save_as == 'document':
            self.collection.insert_one(record.__dict__)

        elif self.save_as == 'field_value':
            self.count += 1
            value = self.format(record)
            query = {'_id': self.document}
            # asctime = record.__dict__['asctime'].split(',')[0].replace('.', '_')
            # field = "({c}) {t}".format(c=self.count, t=asctime)
            field = "({c}) {t}".format(c=self.count, t=self.formatter.formatTime(record, "%Y-%m-%d %H:%M:%S"))
            self.collection.update_one(query, {'$set': {field: value}})
            count_field = 'log_counts.total'
            self.collection.update_one(query, {'$set': {count_field: self.count}})
            if record.__dict__['levelno'] in [logging.DEBUG, logging.INFO,
                                              logging.WARNING, logging.ERROR, logging.CRITICAL]:
                count_field = "log_counts.{}".format(record.__dict__['levelname'].lower())
            else:
                count_field = "log_counts.else"
            self.collection.update_one(query, {'$inc': {count_field: 1}})
            # print(value)

        else:
            super().emit(record)


if __name__ == '__main__':

    logger = logging.getLogger('y_logger')
    logger.setLevel(logging.DEBUG)

    mh = YMongoHandler('test_database', 'log', command=__file__)
    formatter = logging.Formatter('%(asctime)s, %(levelname)s, %(filename)s, %(lineno)d, %(message)s')
    mh.setFormatter(formatter)
    logger.addHandler(mh)

    logger.debug("debug")
    logger.info("info")
    logger.info("info again")
    logger.warning("warning")
    logger.error("error")
    logger.critical("critical")


