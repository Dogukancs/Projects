\# Dynamic City Population Simulation



A Java-based Object-Oriented Programming (OOP) simulation engine that models hierarchical demographic growth, dynamic object instantiation, and automated city splitting based on configurable population thresholds. Built with \*\*Apache Maven\*\* and \*\*Java Faker\*\* for realistic synthetic data generation.



\## Tech Stack \& Tools

\* \*\*Language:\*\* Java (SE)

\* \*\*Build \& Dependency Management:\*\* Apache Maven (`pom.xml`)

\* \*\*Libraries:\*\* `java-faker` (Synthetic citizen, city, district, and neighborhood generation)

\* \*\*IDE:\*\* Eclipse



\## System Architecture \& Class Hierarchy

The simulation models real-world administrative structures using a four-tier composition hierarchy:

\* \*\*`Sehir` (City):\*\* Top-level entity managing a dynamic list of districts and computing aggregate population in real time.

\* \*\*`Ilce` (District):\*\* Mid-level administrative unit aggregating neighborhood populations.

\* \*\*`Mahalle` (Neighborhood):\*\* Lowest administrative unit storing individual citizen objects.

\* \*\*`Kisi` (Citizen):\*\* Atomic data entity holding unique IDs, names, surnames, and ages generated dynamically via \*\*Java Faker\*\*.



\## Core Simulation Mechanics

1\. \*\*Hierarchical Initialization:\*\* Parses user-supplied numeric inputs where tens and ones digits dynamically determine initial district and neighborhood counts.

2\. \*\*Algorithmic Population Growth:\*\* On each simulation turn, computes the digit sum of existing populations to scale demographic expansion and instantiate new `Kisi` objects.

3\. \*\*Dynamic City Splitting:\*\* Automatically splits any city exceeding the \*\*1,000-citizen threshold\*\* into two independent entities, assigning newly generated names via Java Faker.

4\. \*\*Edge-Case \& Exception Handling:\*\* Guards against `ArithmeticException` (division-by-zero) on inputs ending in `0` (e.g., `50`) by enforcing minimum neighborhood constraints and dynamic divisibility checks.



\## How to Build \& Run

```bash

\# Compile and package the project using Maven

mvn clean package



\# Run the simulation via Maven

mvn exec:java -Dexec.mainClass="Main"

