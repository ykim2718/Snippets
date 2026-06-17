import C from '../Constant'

const virtual_db = [
    {
        artist: "Claude Monet",
        painting: "Woman with a Parasol - Madame Monet and Her Son",
        year: 1875,
        image: "https://upload.wikimedia.org/wikipedia/commons/thumb/1/1b/Claude_Monet_-_Woman_with_a_Parasol_-_Madame_Monet_and_Her_Son_-_Google_Art_Project.jpg/800px-Claude_Monet_-_Woman_with_a_Parasol_-_Madame_Monet_and_Her_Son_-_Google_Art_Project.jpg",
    },
    {
        artist: "Claude Monet",
        painting: "Coquelicots, La promenade (Poppies)",
        year: 1873,
        image: "https://upload.wikimedia.org/wikipedia/commons/thumb/2/29/Claude_Monet_037.jpg/1280px-Claude_Monet_037.jpg",
    },
    {
        artist: "Claude Monet",
        painting: "Woman with a Parasol, facing left",
        year: 1886,
        image: "https://upload.wikimedia.org/wikipedia/commons/thumb/3/31/Claude_Monet_023.jpg/800px-Claude_Monet_023.jpg",
        note: "The pictured woman is Suzanne Hoschedé, daughter of Hoschedé, second wife of Claude Monet (1868-1899)",
    },
    {
        artist: "Claude Monet",
        painting: "View at Rouelles, Le Havre",
        year: 1858,
        image: "https://upload.wikimedia.org/wikipedia/commons/4/44/Monet%2C_Claude_-_View_At_Rouelles%2C_Le_Havre_%281858%29.jpg",
        note: "an early work showing the influence of Corot and Courbet",
    },
    {
        artist: "Claude Monet",
        painting: "Snow at Argenteuil",
        year: 1875,
        image: "https://upload.wikimedia.org/wikipedia/commons/thumb/7/7a/Monet_Snow_at_Argenteuil_1875.jpg/1280px-Monet_Snow_at_Argenteuil_1875.jpg",
    },
    {
        artist: "Claude Monet",
        painting: "Water Lilies",
        year: 1919,
        image: "https://upload.wikimedia.org/wikipedia/commons/9/9e/WLA_metmuseum_Water_Lilies_by_Claude_Monet.jpg"
    },
    {
        artist: "Claude Monet",
        painting: "Stormy Sea in Étretat",
        year: 1883,
        medium: "oil on canvas",
        dimensions: "100 cm × 81 cm",
        image: "https://upload.wikimedia.org/wikipedia/commons/thumb/e/ea/Monet-Mer_agit%C3%A9e_%C3%A0_Etretat-MBA-Lyon.jpg/1280px-Monet-Mer_agit%C3%A9e_%C3%A0_Etretat-MBA-Lyon.jpg",
        location: "Musée des Beaux-Arts de Lyon",
    }
]

const ListDemoActionCreator = {
    getLoadingAction(show) {
        return { type: C.IS_LOADING, isLoading: show }
    },
    findMissingItemIndex(items) {
        let missings = []
        virtual_db.forEach((value, index, array) => {
            let found = false
            items.forEach((v, j, a) => {
                if (!found && v.painting === value.painting) {
                    found = true
                }
            })
            if (!found)
                missings.push(index)
        })
        let missingIndex = missings.length > 0 ? missings[0] : -1
        return missingIndex
    },
    addListItem() {
        return (dispatch, getState) => {
            dispatch(this.getLoadingAction(true))   
            let { listItems } = getState().ListDemo
            let missingIndex = this.findMissingItemIndex(listItems)
            setTimeout( () => {
                if (missingIndex >= 0) {
                    // duplicate state to be detectable during deep comparision of states at store, 2019.4.25
                    listItems = JSON.parse(JSON.stringify(listItems))
                    listItems.push(virtual_db[missingIndex])
                    dispatch({ type: C.ADD_ITEM, listItems: listItems })
                    dispatch(this.getLoadingAction(false))
                } else {
                    dispatch(this.getLoadingAction(-1))
                }
            }, 2000) // 1 sec delay to mimic asynchronous operation
        }
    },
    delListItem(id) {
        return { type: C.DEL_ITEM, item_id: id }
    }
}

export default ListDemoActionCreator