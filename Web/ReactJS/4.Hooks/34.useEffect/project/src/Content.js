
import {useEffect, useState} from 'react'

// Side Effects: thuật ngữ lập trình 

// Events: Add/ remove event listener
// Observer pattern: Subcribe / unsubscribe
// Closure
// Timer: setInterval, setTimeout, clearInterval, clearTimeout
// useState
// Mounted/Unmounted
// toán tử ===
// Call API
/** 
 1. UPdate DOM
     - F8 blog title
    2. Call API
    3. Listen DOM events
        - Scroll
        - Resize
    4. Cleanup
        - Remove Listener / Unsubcribe
        - Clear timer
*/

// 1. useEffect(callback)
// 2. useEffect(callback, [])
// 3. useEffect(callback, [deps])

// -------------------
// 1.Callback luôn được gọi sau khi component mounted 
// - gọi callback mỗi khi component re-render
// - gọi callback sau khi component thêm element vào DOM
// 2. useEffect(callback, []). chỉ gọi callback một lần khi component được mounted
function Content(){
    const [title, setTitle] = useState('')
    const [contents, setContents] = useState([])

    useEffect(()=>{
        // console.log('mounted')
        // document.title = title

        // Sử dụng callAPI
        fetch('https://jsonplaceholder.typicode.com/posts')
            .then(res => res.json())
            .then(posts => {
                setContents(posts)
                console.log('abcxyzz')
                // Tạo thành vòng loop gửi fetch liên tục, dẫn đến treo web
                // Giải pháp: sử dụng useEffect dependencies
            })
    }, [])

    return (
        <div>
            <input
                value = {title} 
                onChange={e=> setTitle(e.target.value)}
            />
            <ul>
                {contents.map(content => (
                    <li key={content.id}>{content.title}</li>
                ))}
            </ul>
            {console.log('rendered')}
        </div>
    )
}

export default Content