/**
 * @file MyArray.h
 * @brief Dinamikus tömb pointer alapú objektum tároláshoz.
 *
 * A MyArray egy dinamikus konténer, amely T típusú objektumokra
 * mutató pointereket tárol, és felel azok memóriakezeléséért.
 */
#ifndef MYARRAY_H
#define MYARRAY_H
#include <iostream>

 /**
  * @class MyArray
  * @brief Dinamikus tömb pointerekhez, automatikus memóriakezeléssel.
  * Törléskor felszabadítja az objektumokat
  * @tparam T Tárolt típus
  */
template<typename T>
class MyArray {
	T** data; //Pointer típusú tömb a T típusú objektumok pointereinek tárolására
	int count; //Aktuális elemek száma
	int capacity; //A tömb kapacitása
	/**
	 * @brief Másoló segédfüggvény
	 * Mély másolatot készít a másik tömbrõl clone() segítségével.
	 * @param a A másolandó MyArray
	 */
	void copyfrom(const MyArray& a)
	{
		count = a.count;
		capacity = a.capacity;
		data = new T * [capacity];
		for (int i = 0; i < capacity; i++)
		{
			if (i < count && a.data[i] != nullptr)
			{
				data[i] = a.data[i]->clone();
			}
			else
			{
				data[i] = nullptr;
			}
		}
	}
	/**
	 * @brief Memória felszabadítása
	 * Törli az összes tárolt objektumot és a tömböt
	 */
	void clear()
	{
		for (int i = 0; i < count; i++)
		{
			delete data[i];
		}
		delete[] data;
	}
	/**
	 * @brief Kapacitás növelése
	 * Duplázza a tömb méretét és átmásolja az elemeket.
	 */
	void resize()
	{
		capacity *= 2;
		T** newData = new T * [capacity];
		for (int i = 0; i < capacity; i++)
		{
			if (i < count) newData[i] = data[i]; 
			else newData[i] = nullptr;
		}
		delete[] data;
		data = newData;
	}
public:
	/**
	 * @brief Konstruktor
	 * @param cap Kezdeti kapacitás (alapértelmezett: 10)
	 */
	MyArray(int cap=10) : count(0), capacity(cap)
	{
		data = new T * [capacity];
		for (int i = 0; i < capacity; i++)
		{
			data[i] = nullptr;
		}
	}
	/**
	 * @brief Másoló konstruktor
	 * Mély másolatot készít clone() segítségével.
	 * @param a A másolandó tömb
	 */
	MyArray(const MyArray& a)
	{
		copyfrom(a);
	}
	/**
	 * @brief Értékadó operátor
	 * Elõször felszabadítja a meglévõ adatokat,
	 * majd mély másolatot készít.
	 * @param a A másolandó tömb
	 * @return Referencia önmagára
	 */
	MyArray& operator=(const MyArray& a)
	{
		if (this != &a)
		{
			clear();
			copyfrom(a);
		}
		return *this;
	}
	/**
	 * @brief Destruktor
	 * Felszabadítja az összes tárolt objektumot.
	 */
	~MyArray()
	{
		clear();
	}
	/**
	 * @brief Elem hozzáadása
	 * @param item A hozzáadandó objektum pointere
	 */
	void Add(T* item)
	{
		if (count >= capacity) 
			resize();
		data[count++] = item;
	}
	/**
	 * @brief Elem eltávolítása index alapján
	 * Az adott elemet törli, majd az utolsó elemet
	 * a helyére mozgatja
	 * @param idx Az eltávolítandó elem indexe
	 */
	void Remove(int idx)
	{
		if (idx < 0 || idx >= count)
			return;
		delete data[idx];
		data[idx] = data[count - 1];
		data[count - 1] = nullptr;
		count--;
	}
	/**
	 * @brief Elem elérése index alapján
	 * @param idx Index
	 * @return Pointer az elemre
	 */
	T* operator[](int idx)
	{
		return data[idx];
	}
	/**
	 * @brief Elem elérése index alapján
	 * @param idx Index
	 * @return Pointer az elemre (const)
	 */
	const T* operator[](int idx) const
	{
		return data[idx];
	}
	/**
	 * @brief Aktuális elemszám lekérése
	 * @return Az elemek száma
	 */
	int size() const
	{
		return count;
	}
};

#endif
