import { Listbox } from '@headlessui/react'
import clsx from 'clsx';
import { IoMdArrowDropdown } from "react-icons/io";

export interface DropdownOption {
  id: any,
  value: any,
  label: string,
  disabled?: boolean
}

interface DropdownProps {
  label?: string
  options: DropdownOption[],
  selectedOption: any,
  setSelectedOption: (value: any) => void,
  disabled?: boolean,
  dropdownClassName?: string,
  listboxLabelClassName?: string,
  listboxButtonClassName?: string,
  listboxOptionsClassName?: string,
  listboxOptionClassName?: string
}

export default function Dropdown({
  label,
  options,
  selectedOption,
  setSelectedOption,
  disabled,
  dropdownClassName,
  listboxLabelClassName,
  listboxButtonClassName,
  listboxOptionsClassName,
  listboxOptionClassName
}: DropdownProps) {  
    return (
      <div className={`relative ${dropdownClassName}`}>
        <Listbox value={selectedOption} onChange={setSelectedOption} disabled={disabled}>
          {label && 
            <Listbox.Label className={clsx(
              `flex justify-center text-sm font-medium leading-6 text-neutral-100 ${listboxLabelClassName}`,
              {
                "text-neutral-500": disabled
              })
            }>
              {label}
            </Listbox.Label>
          }
          <Listbox.Button className={clsx(
              `flex justify-center items-center w-48 rounded-sm h-8 bg-neutral-700 border border-transparent text-left pl-2 mx-auto ${listboxButtonClassName}`,
              {
                "hover:border-transparent active:border-transparent text-neutral-500": disabled,
                "hover:border-neutral-400 active:border-neutral-100": !disabled
              })
          }>
            {selectedOption ? selectedOption.label : "Select an option..."}
            <div className="flex justify-center items-center ml-auto overflow-hidden bg-neutral-800 shadow-inner shadow-neutral-700/50 h-full w-8 text-xl ">
              <IoMdArrowDropdown />
            </div>
          </Listbox.Button>
          <Listbox.Options className={`w-48 block absolute left-1/2 -translate-x-1/2 z-10 bg-neutral-700 mt-2 rounded-sm ${listboxOptionsClassName}`}>
            {options.map((option) => (
              <Listbox.Option
                key={option.id}
                value={option}
                disabled={option.disabled}
                className={`px-2 cursor-pointer hover:bg-neutral-200 hover:text-neutral-800 ${listboxOptionClassName}`}
              >
                {option.label}
              </Listbox.Option>
            ))}
          </Listbox.Options>
        </Listbox>
      </div>
    )
  }