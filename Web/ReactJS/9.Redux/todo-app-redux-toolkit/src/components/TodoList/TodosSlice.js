// const initState = [
//         {id: 1, name: 'Learn Yoga', completed: false, priority: 'Medium'},
//         {id: 2, name: 'Learn Redux', completed: true, priority: 'High'},
//         {id: 3, name: 'Learn JavaScript', completed: false, priority: 'Low'},
// ]


// const todoListReducer = (state = initState, action) =>{

//     switch(action.type){
//         case 'todoList/addTodo':
//             return [...state, action.payload]
//         case 'todoList/toggleTodoStatus': 
//             return state.map(todo => 
//                 todo.id === action.payload ? {...todo ,completed : !todo.completed} : todo)
//         default: 
//             return state
//     }
// }


// export default todoListReducer

import {createSlice} from '@reduxjs/toolkit'

export default createSlice({
    name: 'todoList',
    initialState: [
        {id: 1, name: 'Learn Yoga', completed: false, priority: 'Medium'},
        {id: 2, name: 'Learn Redux', completed: true, priority: 'High'},
        {id: 3, name: 'Learn JavaScript', completed: false, priority: 'Low'},  
    ],
    reducers: {
        addTodo: (state, action) => {
            state.push(action.payload)
        }, // tạo ra 1 action creator
        toggleTodoStatus: (state, action) => {
            const currentTodo = state.find(todo => todo.id === action.payload)
            if (currentTodo){
                currentTodo.completed = !currentTodo.completed
            }
        },
    }
})