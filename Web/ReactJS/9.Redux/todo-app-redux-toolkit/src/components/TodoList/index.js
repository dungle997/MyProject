import { Col, Row, Input, Button, Select, Tag } from 'antd';
import Todo from '../Todo';
import { useDispatch, useSelector } from 'react-redux'
import { v4 as uuidv4} from 'uuid'
import { useState } from 'react'
import { todoListSelector, searchTextSelector, todosRemainingSelector } from '../../redux/selectors'
import todoListSlice from './TodosSlice'

export default function TodoList() {
  const [todoName, setTodoName] = useState('')
  const [priority, setPriority] = useState('Medium')
  // console.log(todoName)

  // const todoList = useSelector(todoListSelector)
  const todoList = useSelector(todosRemainingSelector)

  // const searchText = useSelector(searchTextSelector)
  // console.log(searchText)

  // console.log(todoList)

  const dispatch = useDispatch()

  const handleAddButtonClick = () => {
    dispatch(
      todoListSlice.actions.addTodo({
        id: uuidv4(),
        name: todoName, 
        priority: priority,
        completed: false
    }))

    setTodoName('')
    setPriority('Medium')
  }

  const handleInputChange = (e) => {
    // console.log(e.target.value)
    setTodoName(e.target.value)
  }

  const handlePriorityChange = (value) => {
    // console.log({a})
    setPriority(value)
  }

  return (
    <Row style={{ height: 'calc(100% - 40px)' }}>
      <Col span={24} style={{ height: 'calc(100% - 40px)', overflowY: 'auto' }}>
        {/* <Todo name='Learn React' prioriry='High' />
        <Todo name='Learn Redux' prioriry='Medium' />
        <Todo name='Learn JavaScript' prioriry='Low' /> */}
        {
          todoList.map( todo => <Todo key={todo.id} name={todo.name} prioriry={todo.priority} completed={todo.completed} id={todo.id}/>)
        }
      </Col>
      <Col span={24}>
        <Input.Group style={{ display: 'flex' }} compact>
          {/* <Input value={todoName} onChange={e => handleInputChange(e)}/> */}
          <Input value={todoName} onChange={handleInputChange}/>

          <Select defaultValue="Medium"  value={priority} onChange={handlePriorityChange}>
            <Select.Option value='High' label='High'>
              <Tag color='red'>High</Tag>
            </Select.Option>
            <Select.Option value='Medium' label='Medium'>
              <Tag color='blue'>Medium</Tag>
            </Select.Option>
            <Select.Option value='Low' label='Low'>
              <Tag color='gray'>Low</Tag>
            </Select.Option>
          </Select>
          <Button type='primary' onClick={handleAddButtonClick}>
            Add
          </Button>
        </Input.Group>
      </Col>
    </Row>
  );
}
