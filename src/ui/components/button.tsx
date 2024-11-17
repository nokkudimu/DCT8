import { IButton } from "../interfaces/IButton"

export const Button: React.FC<IButton> = ({
    className,
    children,
    onClick    
}) => { 
    return (
        <div
            className={className}
            onClick={onClick}
            >
        {children}
        </div>
    )
}

export default Button
