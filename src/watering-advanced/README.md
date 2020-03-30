hpp2plantuml -i "*.h" -o output.puml

Generate UML class diagram of States
hpp2plantuml -i "./src/WateringMachine/States/*.h" -o docs/uml/states.puml

Generate UML class diagram of Components
hpp2plantuml -i "./src/WateringMachine/Components/*.h" -i "./src/WateringMachine/Components/StateMachineInterfaces/*.h" -o docs/uml/components.puml