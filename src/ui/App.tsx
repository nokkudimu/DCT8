import { useEffect, useState } from 'react'
import { GrimoiresOfTheGreatAncientsSVG } from './components/grimoiresOfTheGreatAncientsSvg.tsx'
import './styles/main.css'
import Button from './components/button.tsx';

function App() {

  const [introIsRunning, setIntroIsRunning] = useState<boolean>(true);
  useEffect(() => {
    setInterval(() => {
      setIntroIsRunning(false);
    }, 8000)
  });

  // starting intro
  if (introIsRunning) {
    return (
      <div>
        <GrimoiresOfTheGreatAncientsSVG />
      </div>
    )
  }
  // main app
  return (
    <div>
      <Button
        className='button'
        onClick={() => console.log('Clicked')}>
        <p
        className='content'>
          Click
        </p>
      </Button>
    </div>
  )
}

export default App
