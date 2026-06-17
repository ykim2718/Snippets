/*/////////////////////////////////////////////////////////////////////////////////////////////////

yMongo.js
based on node.js backend
y, 2019.5.21 - 22, 5.28, 5.29, 5.30, 5.31

/////////////////////////////////////////////////////////////////////////////////////////////////*/

const version = '0.0.2019.5.31'

const MongoClient = require('mongodb').MongoClient
const assert = require('assert')  // node.js module; no need to install
const check = require('check-types')
const _ = require('underscore')

const print = console.log

///////////////////////////////////////////////////////////////////////////////////////////////////


function sleep_expensively(delay_sec) {
    // y, 2019.5.30
    delay_msec = delay_sec * 1000
    let then = new Date().getTime()
    now = then
    while ((now - then) < delay_msec) {
        now = new Date().getTime()
    }
}

async function read_documents_async({ query, projection = null, url }) {
    /*
    y, 2019.5.28, 5.30

    Note
    ----
    . Do not use project in .find(); use .project() instead; .find({}, projection) doesn't work in
        node.js but works in Robo 3T. [1]

    Reference
    ---------
    [1] https://stackoverflow.com/questions/48451300/projection-not-working-with-db-collection-find-in-mongo
    */
    let { hostname, port, pathname } = new URL(url)
    let [database_name, collection_name] = pathname.slice(1, pathname.length).split('.')
    return new Promise(resolve => {
        MongoClient.connect(`mongodb://${hostname}:${port}`, { useNewUrlParser: true },
            (err, client) => {
                if (err) {
                    resolve({ count: 0, res: null, err: 'no response from url' })
                } else {
                    const collection = client.db(database_name).collection(collection_name)
                    collection.find(query).project(projection).toArray((err, res) => {
                        count = err ? 0 : res.length
                        result = { count: count, res: res, err: err }
                        resolve(result)
                    })
                    client.close()
                }
            })
    })
}

async function write_documents_async({ docs, url }) {
    /*
    y, 2019.5.21 - 22, 5.28, 5.30
    */
    docs = check.array(docs) ? docs : [docs]
    let { hostname, port, pathname } = new URL(url)
    let [database_name, collection_name] = pathname.slice(1, pathname.length).split('.')
    return new Promise(resolve => {
        MongoClient.connect(`mongodb://${hostname}:${port}`, { useNewUrlParser: true },
            (err, client) => {
                if (err) {
                    resolve({ count: 0, res: null, err: 'no response from url' })
                } else {
                    const collection = client.db(database_name).collection(collection_name)
                    collection.insertMany(docs, (err, res) => {
                        count = err ? 0 : Object.keys(res.insertedIds).length
                        result = { count: count, res: res, err: err }
                        resolve(result)
                    })
                    client.close()
                }
            })
    })
}

async function overwrite_document_async({ query, doc, url }) {
    /*
    y, 2019.5.30
    */
    let { hostname, port, pathname } = new URL(url)
    let [database_name, collection_name] = pathname.slice(1, pathname.length).split('.')
    return new Promise(resolve => {
        MongoClient.connect(`mongodb://${hostname}:${port}`, { useNewUrlParser: true },
            (err, client) => {
                if (err) {
                    resolve({ count: 0, res: null, err: 'no response from url' })
                } else {
                    const collection = client.db(database_name).collection(collection_name)
                    collection.insertMany(docs, (err, res) => {
                        count = err ? 0 : res.lastErrorObject.n
                        if (count == 1) {
                            result = { count: count, res: res, err: err }
                            resolve(result)
                        } else if (count == 0) {
                            write_documents_async({ docs: [doc], url }).then(resolve)
                        } else if (count > 1) {
                            throw `Found unexpected count ${count}`
                        }
                    })
                    client.close()
                }
            })
    })
}

async function aggregate_documents_async({ pipeline, url, ...aggregate_options }) {
    /*
    y, 2019.5.28, 5.30
    */
    assert(check.array(pipeline))
    let { hostname, port, pathname } = new URL(url)
    let [database_name, collection_name] = pathname.slice(1, pathname.length).split('.')
    return new Promise(resolve => {
        MongoClient.connect(`mongodb://${hostname}:${port}`, { useNewUrlParser: true },
            (err, client) => {
                if (err) {
                    resolve({ count: 0, res: null, err: 'no response from url' })
                } else {
                    const collection = client.db(database_name).collection(collection_name)
                    collection.aggregate(pipeline, aggregate_options).toArray((err, res) => {
                        count = err ? 0 : res.length
                        result = { count: count, res: res, err: err }
                        resolve(result)
                    })
                    client.close()
                }
            })
    })
}


async function delete_documents_async({ query, one_or_many = 'many', url, ...delete_options }) {
    /*
    y, 2019.5.31
    */
    assert(['one', 'many'].includes(one_or_many), `should be one or many but got ${one_or_many}`)
    assert(check.array(pipeline))
    let { hostname, port, pathname } = new URL(url)
    let [database_name, collection_name] = pathname.slice(1, pathname.length).split('.')
    return new Promise(resolve => {
        MongoClient.connect(`mongodb://${hostname}:${port}`, { useNewUrlParser: true },
            (err, client) => {
                if (err) {
                    resolve({ count: 0, res: null, err: 'no response from url' })
                } else {
                    const collection = client.db(database_name).collection(collection_name)
                    remove = one_or_many == 'one' ? collection.deleteOne : collection.deleteMany
                    remove = remove.bind(collection)
                    remove(query, delete_options, delete_options, (err, res) => {
                        count = res.deletedCount
                        result = { count: count, res: res, err: err }
                        resolve(result)
                    })
                    client.close()  // Note: client.close() precedes callback of remove(), 2019.5.31
                }
            })
    })
}

///////////////////////////////////////////////////////////////////////////////////////////////////

if (typeof module != 'undefined' && !module.parent) {
    const randInt = (min, max) => Math.floor(Math.random() * (max - min) + min)
    let url = 'mongodb://localhost:27017/test_database.test_collection'
    let my_doc = { foo: randInt(0, 9), bar: randInt(1, 5), zoo: randInt(5, 9) }
    my_doc['createdAt'] = new Date()  // .toLocaleString()
    console.log('Start at', my_doc['createdAt'].toLocaleString())
    let example = 'read_async'
    switch (example) {
        case 'read_async':
            console.log(`<${example}>`)
            let query = { 'createdAt': { '$gt': new Date('2019-5-25') } }
            let projection = { '_id': 0, 'foo': 0, 'bar': 0 }
            read_documents_async({ query, projection, url })
                .then(({ count, res, err }) => console.log('ASYNC READING:', count, '\n', res))
            break
        case 'write_sync':
            (async () => {
                console.log(`<${example}>`)
                let { count, res, err } = await write_documents_async({ docs: my_doc, url })
                console.log(count)
            })()
            break
        case 'write_async':
            console.log(`<${example}>`)
            write_documents_async({ docs: my_doc, url })
                .then(({ count, res, err }) => console.log('ASYNC WRITING:', count, '\n', res))
            break
        case 'overwrite_async':
            console.log(`<${example}>`)
            let query = { 'foo': 99, 'bar': 2 }
            overwrite_document_async({ query, doc: my_doc, url })
                .then(({ count, res, err }) => console.log('ASYNC OVERWRITING:', count, '\n', res))
            break
        case 'pipeline_async':
            console.log(`<${example}>`)
            let pipeline = [
                { '$match': { 'foo': { '$gt': 1 } } },
                { '$project': { '_id': 0, 'createdAt': 0 } },
                { '$group': { '_id': '$foo', 'bars': { '$push': '$bar' } } },
            ]
            aggregate_documents_async({ pipeline, url, allowDiskUse: true })
                .then(({ count, res, err }) => console.log('ASYNC AGGREGATING:', count, '\n', res))
            break
        case 'delete_async':
            console.log(`<${example}>`)
            let query = { 'foo': 4, 'bar': 3 }
            overwrite_document_async({ query, url, one_or_many: 'one' })
                .then(({ count, res, err }) => console.log('ASYNC DELETING:', count, '\n', res))
            break
    }
    console.log('Done ...')
} else {
    module.exports = {
        version,
        read_documents_async,
        write_documents_async,
        overwrite_document_async,
        aggregate_documents_async,
        delete_documents_async,
    }
}