import React, { useState } from "react";
import "./App.css";
import { useDragAndDrop } from "./useDragAndDrop";

export default function App() {
    const [isActive, setIsActive] = useState(false);
    const dropDownMenu = () => setIsActive(!isActive);

    const imgRef = React.createRef();
    const position = useDragAndDrop(imgRef, { x: 0, y: 0 });

    const [file, setFile] = useState();
    const selectImage = (e) => {
        setFile(URL.createObjectURL(e.target.files[0]));
        // обнуляем стартовую позицию изображения
        position.x = 0;
        position.y = 0;
    }

    return (
        <div className="app">
            <div className="menu-container">
                <div onClick={dropDownMenu} className="menu-trigger">
                    <span>File</span>
                </div>
                <nav className={`menu ${isActive ? 'active' : 'inactive'}`}>
                    <ul>
                        <li className="menu_open">
                            <label htmlFor="files">Open</label>
                            <input onChange={selectImage} className="open_button_hidden" id="files"  type="file" accept="image/jpeg,image/png,image/bmp" />
                        </li>
                    </ul>
                </nav>
            </div>
            <div className="image-container">
                <img ref={imgRef} id="image" className="image" src={file} draggable="false"
                    style={{ left: position.x, top: position.y }} />
            </div>    
        </div>
    );
}