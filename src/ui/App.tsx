import { useEffect, useState } from 'react'
import { GrimoiresOfTheGreatAncientsSVG } from './components/grimoiresOfTheGreatAncientsSvg.tsx'
import './styles/index.css'

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
      
    </div>
  )
}

export default App
