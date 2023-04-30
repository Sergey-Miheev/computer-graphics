import { useEffect, useState } from "react";

export const useDragAndDrop = (elementRef, initPosition,) => {
    const [position, setPosition] = useState(initPosition);

    let startDragX = 0;
    let startDragY = 0;

    useEffect(() => {
        // подписка когда кнопка нажата, компонент размонтирован - отписка
        if (elementRef.current)
            elementRef.current.addEventListener("mousedown", dragHandler);
        return () => {
            if (elementRef.current)
                elementRef.current.removeEventListener("mousedown", dragHandler);
        };
    });

    const dragHandler = (e) => {
        startDragX = e.pageX;
        startDragY = e.pageY;

        document.addEventListener("mousemove", onMove);
        // кнопка отпущена
        document.addEventListener("mouseup", onDrop);
    };

    const onMove = (e) => {
        const newX = position.x + e.pageX - startDragX;
        const newY = position.y + e.pageY - startDragY;
        setPosition({ x: newX, y: newY });
    };

    const onDrop = () => {
        document.removeEventListener("mousemove", onMove);
        document.removeEventListener("mouseup", onDrop);
    };

    return position;
};