/**
  Handout #2: Persistent Entity ADT
  Francisco Cunha, #45412
 */

// ------------------------------------------------------------------------

datatype Sex = Male | Female
datatype QueryResult<T> = None | Some(T)

// ------------------------------------------------------------------------

class Database {

  /* MARK: Class/Instance Fields. */

  static const MAX_CAPACITY := 100;

  var userCollection: array<User?>;
  var size: nat;

  /* MARK: Constructor. */

  constructor()
    ensures RepInv()
    ensures fresh(userCollection)
  {
    userCollection := new User?[MAX_CAPACITY];
    size := 0;
  }

  /* MARK: Representation Invariant. */

  predicate RepInv()
    reads this`userCollection, this`size
  {
    0 <= size <= userCollection.Length
  }

  /* MARK: Helper Functions. */

  function method IlegalId(id: int): bool
    reads this`userCollection
  {
    !(0 <= id < userCollection.Length)
  }

  function method isFull(): bool
    reads this`size, this`userCollection
  {
    size >= userCollection.Length
  }

  /* MARK: Instance Methods. */

  method Find(id: int) returns (result: QueryResult<User>)
    requires RepInv()
    ensures RepInv()
    ensures IlegalId(id) || userCollection[id] == null ==> result == None
  {
    if IlegalId(id) || userCollection[id] == null {
      return None;
    } else {
      var userClone := userCollection[id].Clone();
      return Some(userClone);
    }
  }

  method Add(user: User)
    modifies userCollection, this`size
    requires RepInv()
    ensures RepInv()
    ensures user == old(user)
    ensures size >= old(size)
    ensures size < userCollection.Length - 1 ==> size > old(size)
  {
    if 0 <= size < userCollection.Length {
      userCollection[size] := user.Clone();
      size := size + 1;   
    }
  }

  /**
  Update the fields (e.g. re-save) of an existing element in the collection.
  */
  method UpdateExistent(user: User)
    modifies userCollection
    requires RepInv()
    ensures RepInv()
  {
    var id := user.getId();
    if !IlegalId(id) {
      userCollection[id] := user.Clone();
    }
  }

  method Delete(id: int)
    modifies userCollection
    requires RepInv()
    ensures RepInv()
    ensures 0 <= id < userCollection.Length ==> userCollection[id] == null 
  {
    if 0 <= id < userCollection.Length {
      userCollection[id] := null;
    }
  }
}

// ------------------------------------------------------------------------

class User {

  /* MARK: Instance Fields. */

  var associatedDatabase: Database?;
  var sex: Sex;
  var name: string;
  var age: nat;
  var id: int;

  /* MARK: Representation Invariant. */

  predicate RepInv()
    reads this
  {
    id >= -1
  }

  /* MARK: State Definitions. */

  predicate TransientState()
    reads this
  {
    RepInv() && id == -1 && associatedDatabase == null
  }

  predicate PersistentState()
    reads this, this.associatedDatabase
  {
    RepInv() && id >= 0 && associatedDatabase != null && associatedDatabase.RepInv()
  }

  predicate DetachedState()
    reads this
  {
    RepInv() && id >= 0 && associatedDatabase == null
  }

  /* MARK: Constructor. */

  constructor(name: string, sex: Sex, age: nat)
    ensures RepInv()
    ensures TransientState()
  {
    this.associatedDatabase := null;
    this.name := name;
    this.sex := sex;
    this.age := age;
    this.id := -1;
  }

  /* Getters and Setters. */

  method getName() returns (name: string)
  {
    return this.name;
  }

  method setName(newName: string)
    modifies this`name
  {
    this.name := newName;
  }

  method getSex() returns (sex: Sex)
  {
    return this.sex;
  }

  method setSex(newSex: Sex)
    modifies this`sex
  {
    this.sex := newSex;
  }

  method getAge() returns (age: nat)
  {
    return this.age;
  }

  method setAge(newAge: nat)
    modifies this`age
  {
    this.age := newAge;
  }

  method getId() returns (id: int)
  {
    return this.id;
  }

  method setId(newId: int)
    modifies this`id
  {
    this.id := newId;
  }

  method getAssociatedDatabase() returns (db: Database?)
  {
    return this.associatedDatabase;
  }

  method setAssociatedDatabase(newAssociatedDatabase: Database?)
    modifies this`associatedDatabase
  {
    this.associatedDatabase := newAssociatedDatabase;
  }

  /* MARK: Clone. */

  method Clone() returns (clonedUser: User)
    ensures fresh(clonedUser)
    ensures this == old(this)
  {
    clonedUser := new User(this.name, this.sex, this.age);
    clonedUser.setAssociatedDatabase(this.associatedDatabase);
    clonedUser.setId(this.id);
  }

  /* MARK: Instance Methods. */

  method Save(associatedDatabase: Database) returns (savedSuccessfully: bool)
    modifies this`id, this`associatedDatabase, associatedDatabase.userCollection, associatedDatabase`size
    requires associatedDatabase.RepInv()
    requires TransientState()
    ensures associatedDatabase.RepInv()
    ensures !associatedDatabase.isFull() ==> PersistentState()
    ensures savedSuccessfully ==> PersistentState()
    ensures savedSuccessfully ==> this.associatedDatabase == associatedDatabase
  {
    savedSuccessfully := false;
    if !associatedDatabase.isFull() {
      this.associatedDatabase := associatedDatabase;
      this.id := associatedDatabase.size;
      associatedDatabase.Add(this);
      savedSuccessfully := true;
    }
  }

  method SaveChanges()
    modifies this`associatedDatabase, this.associatedDatabase.userCollection
    requires PersistentState()
    ensures PersistentState()
    ensures this.id == old(this.id)
    ensures this.associatedDatabase == old(this.associatedDatabase)
    ensures this.associatedDatabase.userCollection == old(this.associatedDatabase.userCollection)
  {
    this.associatedDatabase.UpdateExistent(this);
  }

  method Update(associatedDatabase: Database)
    modifies this`associatedDatabase
    requires associatedDatabase.RepInv()
    ensures associatedDatabase.RepInv()
    requires DetachedState()
    ensures PersistentState()
  {
    this.associatedDatabase := associatedDatabase;
  }

  method Close()
    modifies this`associatedDatabase
    requires PersistentState()
    ensures DetachedState()
  {
    this.associatedDatabase := null;
  }

  method Delete()
    modifies this`id, this`associatedDatabase, this.associatedDatabase.userCollection
    requires PersistentState()
    ensures TransientState()
  {
    associatedDatabase.Delete(this.id);
    this.associatedDatabase := null;
    this.id := -1;
  }
}
