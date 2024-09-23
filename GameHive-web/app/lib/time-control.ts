import { DropdownOption } from "../ui/dropdown";

export interface ITimeControl {
    baseMillis: number;
    incrementMillis: number;
};

export function getTimeControl(id: number): ITimeControl {
    const timeControl: ITimeControl = {baseMillis: 0, incrementMillis: 0};
    switch(id) {
        case 0:
            timeControl.baseMillis = 60000;
            timeControl.incrementMillis = 0;
            break;
        case 1:
            timeControl.baseMillis = 300000;
            timeControl.incrementMillis = 0;
            break;
        case 2:
            timeControl.baseMillis = 300000;
            timeControl.incrementMillis = 3000;
            break;  
        case 3:
            timeControl.baseMillis = 600000;
            timeControl.incrementMillis = 0;
            break;   
        case 4:
            timeControl.baseMillis = 600000;
            timeControl.incrementMillis = 5000;
            break;    
        case 5:
            timeControl.baseMillis = 1800000;
            timeControl.incrementMillis = 0;
            break; 
        case 6:
            timeControl.baseMillis = 1800000;
            timeControl.incrementMillis = 30000;
            break; 
        default:
            break;   
    }
    return timeControl;
}

export const timeControlOptions: DropdownOption[] = [
  {
    id: "bullet",
    value: 0,
    label: "1 minute base | 0 second increment",
  },
  {
    id: "blitz",
    value: 1,
    label: "5 minute base | 0 second increment",
  },
  {
    id: "blitz-incr",
    value: 2,
    label: "5 minute base | 3 second increment",
  },
  {
    id: "rapid",
    value: 3,
    label: "10 minute base | 0 second increment",
  },
  {
    id: "rapid-incr",
    value: 4,
    label: "10 minute base | 5 second increment",
  },
  {
    id: "classical",
    value: 5,
    label: "10 minute base | 5 second increment",
  },
  {
    id: "classical-incr",
    value: 6,
    label: "30 minute base | 30 second increment",
  },
];
