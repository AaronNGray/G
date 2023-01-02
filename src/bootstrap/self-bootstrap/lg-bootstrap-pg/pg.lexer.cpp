#include "g/LexicalAnalyserGenerator/LexicalGenerator.h"
#include "g/LexicalAnalyserGenerator/LexicalMachine.h"
#include "g/LexicalAnalyserGenerator/LexicalContext.h"
#include "g/LexicalAnalyserGenerator/RegularGrammar.h"
#include "g/Actions.h"

using namespace G::LexicalAnalyserGenerator;

FileName filename("pg");
LexicalGenerator* pg_LexicalGenerator = new LexicalGenerator(filename, new LexicalMachine("LG", false, {
  new LexicalContext("INITIAL", new RegularGrammar(
      RegularGrammar::newSelection(
        RegularGrammar::newSelection(
          RegularGrammar::newSelection(
            RegularGrammar::newSelection(
              RegularGrammar::newSelection(
                RegularGrammar::newSelection(
                  RegularGrammar::newSelection(
                    RegularGrammar::newSelection(
                      RegularGrammar::newSequence(
                        RegularGrammar::newSequence(
                          RegularGrammar::newSequence(
                            RegularGrammar::newSequence(
                              RegularGrammar::newSequence(
                                RegularGrammar::newSequence(
                                  RegularGrammar::newSequence(
                                    RegularGrammar::newCharacterClass(CharacterClass( Char('g'))),
                                    RegularGrammar::newCharacterClass(CharacterClass( Char('r')))
                                  ),
                                  RegularGrammar::newCharacterClass(CharacterClass( Char('a')))
                                ),
                                RegularGrammar::newCharacterClass(CharacterClass( Char('m')))
                              ),
                              RegularGrammar::newCharacterClass(CharacterClass( Char('m')))
                            ),
                            RegularGrammar::newCharacterClass(CharacterClass( Char('a')))
                          ),
                          RegularGrammar::newCharacterClass(CharacterClass( Char('r')))
                        ),
                        RegularGrammar::newEnd(0)
                      ),
                      RegularGrammar::newSequence(
                        RegularGrammar::newSequence(
                          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('A', 'Z'), Char('_'), Range('a', 'z')}))),
                          RegularGrammar::newKleene(
                            RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '9'), Range('A', 'Z'), Char('_'), Range('a', 'z')})))
                          )
                        ),
                        RegularGrammar::newEnd(1)
                      )
                    ),
                    RegularGrammar::newSequence(
                      RegularGrammar::newCharacterClass(CharacterClass( Char('"'))),
                      RegularGrammar::newEnd(2)
                    )
                  ),
                  RegularGrammar::newSequence(
                    RegularGrammar::newCharacterClass(CharacterClass( Char('{'))),
                    RegularGrammar::newEnd(3)
                  )
                ),
                RegularGrammar::newSequence(
                  RegularGrammar::newSequence(
                    RegularGrammar::newCharacterClass(CharacterClass( Char('/'))),
                    RegularGrammar::newCharacterClass(CharacterClass( Char('*')))
                  ),
                  RegularGrammar::newEnd(4)
                )
              ),
              RegularGrammar::newSequence(
                RegularGrammar::newSequence(
                  RegularGrammar::newCharacterClass(CharacterClass( Char('/'))),
                  RegularGrammar::newCharacterClass(CharacterClass( Char('/')))
                ),
                RegularGrammar::newEnd(5)
              )
            ),
            RegularGrammar::newSequence(
              RegularGrammar::newSequence(
                RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\t'), Char(' ')}))),
                RegularGrammar::newKleene(
                  RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\t'), Char(' ')})))
                )
              ),
              RegularGrammar::newEnd(6)
            )
          ),
          RegularGrammar::newSequence(
            RegularGrammar::newSequence(
              RegularGrammar::newOptional(
                RegularGrammar::newCharacterClass(CharacterClass( Char('\r')))
              ),
              RegularGrammar::newCharacterClass(CharacterClass( Char('\n')))
            ),
            RegularGrammar::newEnd(7)
          )
        ),
        RegularGrammar::newSequence(
          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true)),
          RegularGrammar::newEnd(8)
        )
      )
    )
  ),
  new LexicalContext("GRAMMAR", new RegularGrammar(
      RegularGrammar::newSelection(
        RegularGrammar::newSelection(
          RegularGrammar::newSelection(
            RegularGrammar::newSelection(
              RegularGrammar::newSelection(
                RegularGrammar::newSelection(
                  RegularGrammar::newSelection(
                    RegularGrammar::newSelection(
                      RegularGrammar::newSelection(
                        RegularGrammar::newSelection(
                          RegularGrammar::newSelection(
                            RegularGrammar::newSelection(
                              RegularGrammar::newSelection(
                                RegularGrammar::newSelection(
                                  RegularGrammar::newSelection(
                                    RegularGrammar::newSelection(
                                      RegularGrammar::newSelection(
                                        RegularGrammar::newSelection(
                                          RegularGrammar::newSelection(
                                            RegularGrammar::newSelection(
                                              RegularGrammar::newSelection(
                                                RegularGrammar::newSelection(
                                                  RegularGrammar::newSelection(
                                                    RegularGrammar::newSelection(
                                                      RegularGrammar::newSelection(
                                                        RegularGrammar::newSelection(
                                                          RegularGrammar::newSelection(
                                                            RegularGrammar::newSelection(
                                                              RegularGrammar::newSelection(
                                                                RegularGrammar::newSelection(
                                                                  RegularGrammar::newSelection(
                                                                    RegularGrammar::newSequence(
                                                                      RegularGrammar::newSequence(
                                                                        RegularGrammar::newSequence(
                                                                          RegularGrammar::newSequence(
                                                                            RegularGrammar::newCharacterClass(CharacterClass( Char('t'))),
                                                                            RegularGrammar::newCharacterClass(CharacterClass( Char('e')))
                                                                          ),
                                                                          RegularGrammar::newCharacterClass(CharacterClass( Char('r')))
                                                                        ),
                                                                        RegularGrammar::newCharacterClass(CharacterClass( Char('m')))
                                                                      ),
                                                                      RegularGrammar::newEnd(9)
                                                                    ),
                                                                    RegularGrammar::newSequence(
                                                                      RegularGrammar::newSequence(
                                                                        RegularGrammar::newSequence(
                                                                          RegularGrammar::newSequence(
                                                                            RegularGrammar::newSequence(
                                                                              RegularGrammar::newSequence(
                                                                                RegularGrammar::newSequence(
                                                                                  RegularGrammar::newCharacterClass(CharacterClass( Char('n'))),
                                                                                  RegularGrammar::newCharacterClass(CharacterClass( Char('o')))
                                                                                ),
                                                                                RegularGrammar::newCharacterClass(CharacterClass( Char('n')))
                                                                              ),
                                                                              RegularGrammar::newCharacterClass(CharacterClass( Char('t')))
                                                                            ),
                                                                            RegularGrammar::newCharacterClass(CharacterClass( Char('e')))
                                                                          ),
                                                                          RegularGrammar::newCharacterClass(CharacterClass( Char('r')))
                                                                        ),
                                                                        RegularGrammar::newCharacterClass(CharacterClass( Char('m')))
                                                                      ),
                                                                      RegularGrammar::newEnd(10)
                                                                    )
                                                                  ),
                                                                  RegularGrammar::newSequence(
                                                                    RegularGrammar::newSequence(
                                                                      RegularGrammar::newSequence(
                                                                        RegularGrammar::newSequence(
                                                                          RegularGrammar::newSequence(
                                                                            RegularGrammar::newCharacterClass(CharacterClass( Char('s'))),
                                                                            RegularGrammar::newCharacterClass(CharacterClass( Char('t')))
                                                                          ),
                                                                          RegularGrammar::newCharacterClass(CharacterClass( Char('a')))
                                                                        ),
                                                                        RegularGrammar::newCharacterClass(CharacterClass( Char('r')))
                                                                      ),
                                                                      RegularGrammar::newCharacterClass(CharacterClass( Char('t')))
                                                                    ),
                                                                    RegularGrammar::newEnd(11)
                                                                  )
                                                                ),
                                                                RegularGrammar::newSequence(
                                                                  RegularGrammar::newSequence(
                                                                    RegularGrammar::newSequence(
                                                                      RegularGrammar::newSequence(
                                                                        RegularGrammar::newSequence(
                                                                          RegularGrammar::newSequence(
                                                                            RegularGrammar::newSequence(
                                                                              RegularGrammar::newSequence(
                                                                                RegularGrammar::newSequence(
                                                                                  RegularGrammar::newSequence(
                                                                                    RegularGrammar::newCharacterClass(CharacterClass( Char('p'))),
                                                                                    RegularGrammar::newCharacterClass(CharacterClass( Char('r')))
                                                                                  ),
                                                                                  RegularGrammar::newCharacterClass(CharacterClass( Char('o')))
                                                                                ),
                                                                                RegularGrammar::newCharacterClass(CharacterClass( Char('d')))
                                                                              ),
                                                                              RegularGrammar::newCharacterClass(CharacterClass( Char('u')))
                                                                            ),
                                                                            RegularGrammar::newCharacterClass(CharacterClass( Char('c')))
                                                                          ),
                                                                          RegularGrammar::newCharacterClass(CharacterClass( Char('t')))
                                                                        ),
                                                                        RegularGrammar::newCharacterClass(CharacterClass( Char('i')))
                                                                      ),
                                                                      RegularGrammar::newCharacterClass(CharacterClass( Char('o')))
                                                                    ),
                                                                    RegularGrammar::newCharacterClass(CharacterClass( Char('n')))
                                                                  ),
                                                                  RegularGrammar::newEnd(12)
                                                                )
                                                              ),
                                                              RegularGrammar::newSequence(
                                                                RegularGrammar::newSequence(
                                                                  RegularGrammar::newSequence(
                                                                    RegularGrammar::newSequence(
                                                                      RegularGrammar::newCharacterClass(CharacterClass( Char('c'))),
                                                                      RegularGrammar::newCharacterClass(CharacterClass( Char('o')))
                                                                    ),
                                                                    RegularGrammar::newCharacterClass(CharacterClass( Char('d')))
                                                                  ),
                                                                  RegularGrammar::newCharacterClass(CharacterClass( Char('e')))
                                                                ),
                                                                RegularGrammar::newEnd(13)
                                                              )
                                                            ),
                                                            RegularGrammar::newSequence(
                                                              RegularGrammar::newSequence(
                                                                RegularGrammar::newSequence(
                                                                  RegularGrammar::newSequence(
                                                                    RegularGrammar::newSequence(
                                                                      RegularGrammar::newSequence(
                                                                        RegularGrammar::newCharacterClass(CharacterClass( Char('h'))),
                                                                        RegularGrammar::newCharacterClass(CharacterClass( Char('e')))
                                                                      ),
                                                                      RegularGrammar::newCharacterClass(CharacterClass( Char('a')))
                                                                    ),
                                                                    RegularGrammar::newCharacterClass(CharacterClass( Char('d')))
                                                                  ),
                                                                  RegularGrammar::newCharacterClass(CharacterClass( Char('e')))
                                                                ),
                                                                RegularGrammar::newCharacterClass(CharacterClass( Char('r')))
                                                              ),
                                                              RegularGrammar::newEnd(14)
                                                            )
                                                          ),
                                                          RegularGrammar::newSequence(
                                                            RegularGrammar::newSequence(
                                                              RegularGrammar::newSequence(
                                                                RegularGrammar::newSequence(
                                                                  RegularGrammar::newSequence(
                                                                    RegularGrammar::newSequence(
                                                                      RegularGrammar::newSequence(
                                                                        RegularGrammar::newSequence(
                                                                          RegularGrammar::newCharacterClass(CharacterClass( Char('r'))),
                                                                          RegularGrammar::newCharacterClass(CharacterClass( Char('o')))
                                                                        ),
                                                                        RegularGrammar::newCharacterClass(CharacterClass( Char('o')))
                                                                      ),
                                                                      RegularGrammar::newCharacterClass(CharacterClass( Char('t')))
                                                                    ),
                                                                    RegularGrammar::newCharacterClass(CharacterClass( Char('t')))
                                                                  ),
                                                                  RegularGrammar::newCharacterClass(CharacterClass( Char('y')))
                                                                ),
                                                                RegularGrammar::newCharacterClass(CharacterClass( Char('p')))
                                                              ),
                                                              RegularGrammar::newCharacterClass(CharacterClass( Char('e')))
                                                            ),
                                                            RegularGrammar::newEnd(15)
                                                          )
                                                        ),
                                                        RegularGrammar::newSequence(
                                                          RegularGrammar::newSequence(
                                                            RegularGrammar::newSequence(
                                                              RegularGrammar::newSequence(
                                                                RegularGrammar::newSequence(
                                                                  RegularGrammar::newSequence(
                                                                    RegularGrammar::newSequence(
                                                                      RegularGrammar::newSequence(
                                                                        RegularGrammar::newSequence(
                                                                          RegularGrammar::newCharacterClass(CharacterClass( Char('b'))),
                                                                          RegularGrammar::newCharacterClass(CharacterClass( Char('a')))
                                                                        ),
                                                                        RegularGrammar::newCharacterClass(CharacterClass( Char('s')))
                                                                      ),
                                                                      RegularGrammar::newCharacterClass(CharacterClass( Char('e')))
                                                                    ),
                                                                    RegularGrammar::newCharacterClass(CharacterClass( Char('c')))
                                                                  ),
                                                                  RegularGrammar::newCharacterClass(CharacterClass( Char('l')))
                                                                ),
                                                                RegularGrammar::newCharacterClass(CharacterClass( Char('a')))
                                                              ),
                                                              RegularGrammar::newCharacterClass(CharacterClass( Char('s')))
                                                            ),
                                                            RegularGrammar::newCharacterClass(CharacterClass( Char('s')))
                                                          ),
                                                          RegularGrammar::newEnd(16)
                                                        )
                                                      ),
                                                      RegularGrammar::newSequence(
                                                        RegularGrammar::newSequence(
                                                          RegularGrammar::newSequence(
                                                            RegularGrammar::newSequence(
                                                              RegularGrammar::newSequence(
                                                                RegularGrammar::newSequence(
                                                                  RegularGrammar::newSequence(
                                                                    RegularGrammar::newSequence(
                                                                      RegularGrammar::newCharacterClass(CharacterClass( Char('b'))),
                                                                      RegularGrammar::newCharacterClass(CharacterClass( Char('a')))
                                                                    ),
                                                                    RegularGrammar::newCharacterClass(CharacterClass( Char('s')))
                                                                  ),
                                                                  RegularGrammar::newCharacterClass(CharacterClass( Char('e')))
                                                                ),
                                                                RegularGrammar::newCharacterClass(CharacterClass( Char('t')))
                                                              ),
                                                              RegularGrammar::newCharacterClass(CharacterClass( Char('y')))
                                                            ),
                                                            RegularGrammar::newCharacterClass(CharacterClass( Char('p')))
                                                          ),
                                                          RegularGrammar::newCharacterClass(CharacterClass( Char('e')))
                                                        ),
                                                        RegularGrammar::newEnd(17)
                                                      )
                                                    ),
                                                    RegularGrammar::newSequence(
                                                      RegularGrammar::newSequence(
                                                        RegularGrammar::newSequence(
                                                          RegularGrammar::newSequence(
                                                            RegularGrammar::newSequence(
                                                              RegularGrammar::newSequence(
                                                                RegularGrammar::newSequence(
                                                                  RegularGrammar::newSequence(
                                                                    RegularGrammar::newSequence(
                                                                      RegularGrammar::newSequence(
                                                                        RegularGrammar::newCharacterClass(CharacterClass( Char('r'))),
                                                                        RegularGrammar::newCharacterClass(CharacterClass( Char('e')))
                                                                      ),
                                                                      RegularGrammar::newCharacterClass(CharacterClass( Char('t')))
                                                                    ),
                                                                    RegularGrammar::newCharacterClass(CharacterClass( Char('u')))
                                                                  ),
                                                                  RegularGrammar::newCharacterClass(CharacterClass( Char('r')))
                                                                ),
                                                                RegularGrammar::newCharacterClass(CharacterClass( Char('n')))
                                                              ),
                                                              RegularGrammar::newCharacterClass(CharacterClass( Char('t')))
                                                            ),
                                                            RegularGrammar::newCharacterClass(CharacterClass( Char('y')))
                                                          ),
                                                          RegularGrammar::newCharacterClass(CharacterClass( Char('p')))
                                                        ),
                                                        RegularGrammar::newCharacterClass(CharacterClass( Char('e')))
                                                      ),
                                                      RegularGrammar::newEnd(18)
                                                    )
                                                  ),
                                                  RegularGrammar::newSequence(
                                                    RegularGrammar::newSequence(
                                                      RegularGrammar::newSequence(
                                                        RegularGrammar::newSequence(
                                                          RegularGrammar::newSequence(
                                                            RegularGrammar::newCharacterClass(CharacterClass( Char('u'))),
                                                            RegularGrammar::newCharacterClass(CharacterClass( Char('n')))
                                                          ),
                                                          RegularGrammar::newCharacterClass(CharacterClass( Char('i')))
                                                        ),
                                                        RegularGrammar::newCharacterClass(CharacterClass( Char('o')))
                                                      ),
                                                      RegularGrammar::newCharacterClass(CharacterClass( Char('n')))
                                                    ),
                                                    RegularGrammar::newEnd(19)
                                                  )
                                                ),
                                                RegularGrammar::newSequence(
                                                  RegularGrammar::newSequence(
                                                    RegularGrammar::newSequence(
                                                      RegularGrammar::newSequence(
                                                        RegularGrammar::newSequence(
                                                          RegularGrammar::newSequence(
                                                            RegularGrammar::newSequence(
                                                              RegularGrammar::newSequence(
                                                                RegularGrammar::newCharacterClass(CharacterClass( Char('n'))),
                                                                RegularGrammar::newCharacterClass(CharacterClass( Char('o')))
                                                              ),
                                                              RegularGrammar::newCharacterClass(CharacterClass( Char('n')))
                                                            ),
                                                            RegularGrammar::newCharacterClass(CharacterClass( Char('a')))
                                                          ),
                                                          RegularGrammar::newCharacterClass(CharacterClass( Char('s')))
                                                        ),
                                                        RegularGrammar::newCharacterClass(CharacterClass( Char('s')))
                                                      ),
                                                      RegularGrammar::newCharacterClass(CharacterClass( Char('o')))
                                                    ),
                                                    RegularGrammar::newCharacterClass(CharacterClass( Char('c')))
                                                  ),
                                                  RegularGrammar::newEnd(20)
                                                )
                                              ),
                                              RegularGrammar::newSequence(
                                                RegularGrammar::newSequence(
                                                  RegularGrammar::newSequence(
                                                    RegularGrammar::newSequence(
                                                      RegularGrammar::newCharacterClass(CharacterClass( Char('l'))),
                                                      RegularGrammar::newCharacterClass(CharacterClass( Char('e')))
                                                    ),
                                                    RegularGrammar::newCharacterClass(CharacterClass( Char('f')))
                                                  ),
                                                  RegularGrammar::newCharacterClass(CharacterClass( Char('t')))
                                                ),
                                                RegularGrammar::newEnd(21)
                                              )
                                            ),
                                            RegularGrammar::newSequence(
                                              RegularGrammar::newSequence(
                                                RegularGrammar::newSequence(
                                                  RegularGrammar::newSequence(
                                                    RegularGrammar::newSequence(
                                                      RegularGrammar::newCharacterClass(CharacterClass( Char('r'))),
                                                      RegularGrammar::newCharacterClass(CharacterClass( Char('i')))
                                                    ),
                                                    RegularGrammar::newCharacterClass(CharacterClass( Char('g')))
                                                  ),
                                                  RegularGrammar::newCharacterClass(CharacterClass( Char('h')))
                                                ),
                                                RegularGrammar::newCharacterClass(CharacterClass( Char('t')))
                                              ),
                                              RegularGrammar::newEnd(22)
                                            )
                                          ),
                                          RegularGrammar::newSequence(
                                            RegularGrammar::newSequence(
                                              RegularGrammar::newSequence(
                                                RegularGrammar::newSequence(
                                                  RegularGrammar::newSequence(
                                                    RegularGrammar::newSequence(
                                                      RegularGrammar::newSequence(
                                                        RegularGrammar::newCharacterClass(CharacterClass( Char('e'))),
                                                        RegularGrammar::newCharacterClass(CharacterClass( Char('p')))
                                                      ),
                                                      RegularGrammar::newCharacterClass(CharacterClass( Char('s')))
                                                    ),
                                                    RegularGrammar::newCharacterClass(CharacterClass( Char('i')))
                                                  ),
                                                  RegularGrammar::newCharacterClass(CharacterClass( Char('l')))
                                                ),
                                                RegularGrammar::newCharacterClass(CharacterClass( Char('o')))
                                              ),
                                              RegularGrammar::newCharacterClass(CharacterClass( Char('n')))
                                            ),
                                            RegularGrammar::newEnd(23)
                                          )
                                        ),
                                        RegularGrammar::newSequence(
                                          RegularGrammar::newCharacterClass(CharacterClass( Char(':'))),
                                          RegularGrammar::newEnd(24)
                                        )
                                      ),
                                      RegularGrammar::newSequence(
                                        RegularGrammar::newSequence(
                                          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('A', 'Z'), Char('_'), Range('a', 'z')}))),
                                          RegularGrammar::newKleene(
                                            RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '9'), Range('A', 'Z'), Char('_'), Range('a', 'z')})))
                                          )
                                        ),
                                        RegularGrammar::newEnd(25)
                                      )
                                    ),
                                    RegularGrammar::newSequence(
                                      RegularGrammar::newCharacterClass(CharacterClass( Char('"'))),
                                      RegularGrammar::newEnd(26)
                                    )
                                  ),
                                  RegularGrammar::newSequence(
                                    RegularGrammar::newCharacterClass(CharacterClass( Char('$'))),
                                    RegularGrammar::newEnd(27)
                                  )
                                ),
                                RegularGrammar::newSequence(
                                  RegularGrammar::newCharacterClass(CharacterClass( Char('='))),
                                  RegularGrammar::newEnd(28)
                                )
                              ),
                              RegularGrammar::newSequence(
                                RegularGrammar::newCharacterClass(CharacterClass( Char('|'))),
                                RegularGrammar::newEnd(29)
                              )
                            ),
                            RegularGrammar::newSequence(
                              RegularGrammar::newCharacterClass(CharacterClass( Char(':'))),
                              RegularGrammar::newEnd(30)
                            )
                          ),
                          RegularGrammar::newSequence(
                            RegularGrammar::newCharacterClass(CharacterClass( Char(';'))),
                            RegularGrammar::newEnd(31)
                          )
                        ),
                        RegularGrammar::newSequence(
                          RegularGrammar::newSequence(
                            RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('A', 'Z'), Char('_'), Range('a', 'z')}))),
                            RegularGrammar::newKleene(
                              RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '9'), Range('A', 'Z'), Char('_'), Range('a', 'z')})))
                            )
                          ),
                          RegularGrammar::newEnd(32)
                        )
                      ),
                      RegularGrammar::newSequence(
                        RegularGrammar::newCharacterClass(CharacterClass( Char('"'))),
                        RegularGrammar::newEnd(33)
                      )
                    ),
                    RegularGrammar::newSequence(
                      RegularGrammar::newCharacterClass(CharacterClass( Char('{'))),
                      RegularGrammar::newEnd(34)
                    )
                  ),
                  RegularGrammar::newSequence(
                    RegularGrammar::newCharacterClass(CharacterClass( Char('}'))),
                    RegularGrammar::newEnd(35)
                  )
                ),
                RegularGrammar::newSequence(
                  RegularGrammar::newSequence(
                    RegularGrammar::newCharacterClass(CharacterClass( Char('/'))),
                    RegularGrammar::newCharacterClass(CharacterClass( Char('*')))
                  ),
                  RegularGrammar::newEnd(36)
                )
              ),
              RegularGrammar::newSequence(
                RegularGrammar::newSequence(
                  RegularGrammar::newCharacterClass(CharacterClass( Char('/'))),
                  RegularGrammar::newCharacterClass(CharacterClass( Char('/')))
                ),
                RegularGrammar::newEnd(37)
              )
            ),
            RegularGrammar::newSequence(
              RegularGrammar::newSequence(
                RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\t'), Char(' ')}))),
                RegularGrammar::newKleene(
                  RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\t'), Char(' ')})))
                )
              ),
              RegularGrammar::newEnd(38)
            )
          ),
          RegularGrammar::newSequence(
            RegularGrammar::newSequence(
              RegularGrammar::newOptional(
                RegularGrammar::newCharacterClass(CharacterClass( Char('\r')))
              ),
              RegularGrammar::newCharacterClass(CharacterClass( Char('\n')))
            ),
            RegularGrammar::newEnd(39)
          )
        ),
        RegularGrammar::newSequence(
          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true)),
          RegularGrammar::newEnd(40)
        )
      )
    )
  ),
  new LexicalContext("LEX_STRING_LITERAL", new RegularGrammar(
      RegularGrammar::newSelection(
        RegularGrammar::newSequence(
          RegularGrammar::newCharacterClass(CharacterClass( Char('"'))),
          RegularGrammar::newEnd(41)
        ),
        RegularGrammar::newSequence(
          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true)),
          RegularGrammar::newEnd(42)
        )
      )
    )
  ),
  new LexicalContext("ACTION", new RegularGrammar(
      RegularGrammar::newSelection(
        RegularGrammar::newSelection(
          RegularGrammar::newSelection(
            RegularGrammar::newSelection(
              RegularGrammar::newSelection(
                RegularGrammar::newSelection(
                  RegularGrammar::newSequence(
                    RegularGrammar::newCharacterClass(CharacterClass( Char('{'))),
                    RegularGrammar::newEnd(43)
                  ),
                  RegularGrammar::newSequence(
                    RegularGrammar::newCharacterClass(CharacterClass( Char('}'))),
                    RegularGrammar::newEnd(44)
                  )
                ),
                RegularGrammar::newSequence(
                  RegularGrammar::newCharacterClass(CharacterClass( Char('"'))),
                  RegularGrammar::newEnd(45)
                )
              ),
              RegularGrammar::newSequence(
                RegularGrammar::newSequence(
                  RegularGrammar::newSequence(
                    RegularGrammar::newCharacterClass(CharacterClass( Char('\''))),
                    RegularGrammar::newSequence(
                      RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                      RegularGrammar::newSelection(
                        RegularGrammar::newSelection(
                          RegularGrammar::newSequence(
                            RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '7')}))),
                            RegularGrammar::newKleene(
                              RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '7')})))
                            )
                          ),
                          RegularGrammar::newSequence(
                            RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('X'), Char('x')}))),
                            RegularGrammar::newSequence(
                              RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '9'), Range('A', 'F'), Range('a', 'f')}))),
                              RegularGrammar::newKleene(
                                RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '9'), Range('A', 'F'), Range('a', 'f')})))
                              )
                            )
                          )
                        ),
                        RegularGrammar::newCharacterClass(CharacterClass( Char('\n')))
                      )
                    )
                  ),
                  RegularGrammar::newCharacterClass(CharacterClass( Char('\'')))
                ),
                RegularGrammar::newEnd(46)
              )
            ),
            RegularGrammar::newSequence(
              RegularGrammar::newSequence(
                RegularGrammar::newSequence(
                  RegularGrammar::newCharacterClass(CharacterClass( Char('\''))),
                  RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true))
                ),
                RegularGrammar::newCharacterClass(CharacterClass( Char('\'')))
              ),
              RegularGrammar::newEnd(47)
            )
          ),
          RegularGrammar::newSequence(
            RegularGrammar::newSequence(
              RegularGrammar::newOptional(
                RegularGrammar::newCharacterClass(CharacterClass( Char('\r')))
              ),
              RegularGrammar::newCharacterClass(CharacterClass( Char('\n')))
            ),
            RegularGrammar::newEnd(48)
          )
        ),
        RegularGrammar::newSequence(
          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true)),
          RegularGrammar::newEnd(49)
        )
      )
    )
  ),
  new LexicalContext("CODE", new RegularGrammar(
      RegularGrammar::newSelection(
        RegularGrammar::newSelection(
          RegularGrammar::newSelection(
            RegularGrammar::newSelection(
              RegularGrammar::newSelection(
                RegularGrammar::newSelection(
                  RegularGrammar::newSequence(
                    RegularGrammar::newCharacterClass(CharacterClass( Char('{'))),
                    RegularGrammar::newEnd(50)
                  ),
                  RegularGrammar::newSequence(
                    RegularGrammar::newCharacterClass(CharacterClass( Char('}'))),
                    RegularGrammar::newEnd(51)
                  )
                ),
                RegularGrammar::newSequence(
                  RegularGrammar::newCharacterClass(CharacterClass( Char('"'))),
                  RegularGrammar::newEnd(52)
                )
              ),
              RegularGrammar::newSequence(
                RegularGrammar::newSequence(
                  RegularGrammar::newSequence(
                    RegularGrammar::newCharacterClass(CharacterClass( Char('\''))),
                    RegularGrammar::newSequence(
                      RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                      RegularGrammar::newSelection(
                        RegularGrammar::newSelection(
                          RegularGrammar::newSequence(
                            RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '7')}))),
                            RegularGrammar::newKleene(
                              RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '7')})))
                            )
                          ),
                          RegularGrammar::newSequence(
                            RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('X'), Char('x')}))),
                            RegularGrammar::newSequence(
                              RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '9'), Range('A', 'F'), Range('a', 'f')}))),
                              RegularGrammar::newKleene(
                                RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '9'), Range('A', 'F'), Range('a', 'f')})))
                              )
                            )
                          )
                        ),
                        RegularGrammar::newCharacterClass(CharacterClass( Char('\n')))
                      )
                    )
                  ),
                  RegularGrammar::newCharacterClass(CharacterClass( Char('\'')))
                ),
                RegularGrammar::newEnd(53)
              )
            ),
            RegularGrammar::newSequence(
              RegularGrammar::newSequence(
                RegularGrammar::newSequence(
                  RegularGrammar::newCharacterClass(CharacterClass( Char('\''))),
                  RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true))
                ),
                RegularGrammar::newCharacterClass(CharacterClass( Char('\'')))
              ),
              RegularGrammar::newEnd(54)
            )
          ),
          RegularGrammar::newSequence(
            RegularGrammar::newSequence(
              RegularGrammar::newOptional(
                RegularGrammar::newCharacterClass(CharacterClass( Char('\r')))
              ),
              RegularGrammar::newCharacterClass(CharacterClass( Char('\n')))
            ),
            RegularGrammar::newEnd(55)
          )
        ),
        RegularGrammar::newSequence(
          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true)),
          RegularGrammar::newEnd(56)
        )
      )
    )
  ),
  new LexicalContext("ACTION_DOUBLE_QUOTED_STRING", new RegularGrammar(
      RegularGrammar::newSelection(
        RegularGrammar::newSelection(
          RegularGrammar::newSequence(
            RegularGrammar::newCharacterClass(CharacterClass( Char('"'))),
            RegularGrammar::newEnd(57)
          ),
          RegularGrammar::newSequence(
            RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
            RegularGrammar::newEnd(58)
          )
        ),
        RegularGrammar::newSequence(
          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true)),
          RegularGrammar::newEnd(59)
        )
      )
    )
  ),
  new LexicalContext("ACTION_DOUBLE_QUOTED_STRING_ESCAPE_SEQUENCE", new RegularGrammar(
      RegularGrammar::newSelection(
        RegularGrammar::newSelection(
          RegularGrammar::newSelection(
            RegularGrammar::newSelection(
              RegularGrammar::newSelection(
                RegularGrammar::newSelection(
                  RegularGrammar::newSelection(
                    RegularGrammar::newSelection(
                      RegularGrammar::newSelection(
                        RegularGrammar::newSelection(
                          RegularGrammar::newSelection(
                            RegularGrammar::newSelection(
                              RegularGrammar::newSelection(
                                RegularGrammar::newSequence(
                                  RegularGrammar::newSequence(
                                    RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('X'), Char('x')}))),
                                    RegularGrammar::newSequence(
                                      RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '9'), Range('A', 'F'), Range('a', 'f')}))),
                                      RegularGrammar::newKleene(
                                        RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '9'), Range('A', 'F'), Range('a', 'f')})))
                                      )
                                    )
                                  ),
                                  RegularGrammar::newEnd(60)
                                ),
                                RegularGrammar::newSequence(
                                  RegularGrammar::newSequence(
                                    RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '7')}))),
                                    RegularGrammar::newKleene(
                                      RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Range('0', '7')})))
                                    )
                                  ),
                                  RegularGrammar::newEnd(61)
                                )
                              ),
                              RegularGrammar::newSequence(
                                RegularGrammar::newCharacterClass(CharacterClass( Char('a'))),
                                RegularGrammar::newEnd(62)
                              )
                            ),
                            RegularGrammar::newSequence(
                              RegularGrammar::newCharacterClass(CharacterClass( Char('b'))),
                              RegularGrammar::newEnd(63)
                            )
                          ),
                          RegularGrammar::newSequence(
                            RegularGrammar::newCharacterClass(CharacterClass( Char('f'))),
                            RegularGrammar::newEnd(64)
                          )
                        ),
                        RegularGrammar::newSequence(
                          RegularGrammar::newCharacterClass(CharacterClass( Char('n'))),
                          RegularGrammar::newEnd(65)
                        )
                      ),
                      RegularGrammar::newSequence(
                        RegularGrammar::newCharacterClass(CharacterClass( Char('r'))),
                        RegularGrammar::newEnd(66)
                      )
                    ),
                    RegularGrammar::newSequence(
                      RegularGrammar::newCharacterClass(CharacterClass( Char('t'))),
                      RegularGrammar::newEnd(67)
                    )
                  ),
                  RegularGrammar::newSequence(
                    RegularGrammar::newCharacterClass(CharacterClass( Char('v'))),
                    RegularGrammar::newEnd(68)
                  )
                ),
                RegularGrammar::newSequence(
                  RegularGrammar::newCharacterClass(CharacterClass( Char('\\'))),
                  RegularGrammar::newEnd(69)
                )
              ),
              RegularGrammar::newSequence(
                RegularGrammar::newCharacterClass(CharacterClass( Char('\''))),
                RegularGrammar::newEnd(70)
              )
            ),
            RegularGrammar::newSequence(
              RegularGrammar::newCharacterClass(CharacterClass( Char('"'))),
              RegularGrammar::newEnd(71)
            )
          ),
          RegularGrammar::newSequence(
            RegularGrammar::newCharacterClass(CharacterClass( Char('?'))),
            RegularGrammar::newEnd(72)
          )
        ),
        RegularGrammar::newSequence(
          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true)),
          RegularGrammar::newEnd(73)
        )
      )
    )
  ),
  new LexicalContext("COMMENT", new RegularGrammar(
      RegularGrammar::newSelection(
        RegularGrammar::newSelection(
          RegularGrammar::newSequence(
            RegularGrammar::newSequence(
              RegularGrammar::newCharacterClass(CharacterClass( Char('*'))),
              RegularGrammar::newCharacterClass(CharacterClass( Char('/')))
            ),
            RegularGrammar::newEnd(74)
          ),
          RegularGrammar::newSequence(
            RegularGrammar::newSequence(
              RegularGrammar::newOptional(
                RegularGrammar::newCharacterClass(CharacterClass( Char('\r')))
              ),
              RegularGrammar::newCharacterClass(CharacterClass( Char('\n')))
            ),
            RegularGrammar::newEnd(75)
          )
        ),
        RegularGrammar::newSequence(
          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true)),
          RegularGrammar::newEnd(76)
        )
      )
    )
  ),
  new LexicalContext("SINGLE_LINE_COMMENT", new RegularGrammar(
      RegularGrammar::newSelection(
        RegularGrammar::newSequence(
          RegularGrammar::newSequence(
            RegularGrammar::newOptional(
              RegularGrammar::newCharacterClass(CharacterClass( Char('\r')))
            ),
            RegularGrammar::newCharacterClass(CharacterClass( Char('\n')))
          ),
          RegularGrammar::newEnd(77)
        ),
        RegularGrammar::newSequence(
          RegularGrammar::newCharacterClass(CharacterClass( Ranges( {Char('\n'), Char('\r')}), true)),
          RegularGrammar::newEnd(78)
        )
      )
    )
  )},
  {
	{ 0, "{ currentValue.Identifier = root->newIdentifier(text()); return pgParser::KEYWORD_GRAMMAR; }", 35},
	{ 1, "{\n\t\t\t\t\t\t\t\t\t\tcurrentValue.Identifier = root->newIdentifier(text());\n\t\t\t\t\t\t\t\t\t\treturn pgParser::IDENTIFIER;\n\t\t\t\t\t\t\t\t\t}", 37},
	{ 2, "{ push(Context::LEX_STRING_LITERAL); stringLiteral = \"\"; return IGNORE; }", 41},
	{ 3, "{ push(Context::GRAMMAR); return pgParser::OPERATOR_OPEN_CURLY_BRACE; }", 43},
	{ 4, "{ push(Context::COMMENT); return IGNORE; }", 45},
	{ 5, "{ push(Context::SINGLE_LINE_COMMENT); return IGNORE; }", 46},
	{ 6, "{ return IGNORE; }", 48},
	{ 7, "{ newLine(); return IGNORE; }", 49},
	{ 8, "{ std::cout << \"Invalid chararcter '\" << toString(*begin()) << \"'\\\n\"; return IGNORE; }", 50},
	{ 9, "{ currentValue.Identifier = root->newIdentifier(text()); return pgParser::KEYWORD_TERM; }", 54},
	{ 10, "{ currentValue.Identifier = root->newIdentifier(text()); return pgParser::KEYWORD_NONTERM; }", 55},
	{ 11, "{ currentValue.Identifier = root->newIdentifier(text()); return pgParser::KEYWORD_START; }", 56},
	{ 12, "{ currentValue.Identifier = root->newIdentifier(text()); return pgParser::KEYWORD_PRODUCTION; }", 58},
	{ 13, "{ currentValue.Identifier = root->newIdentifier(text()); bracket_mode = MODE::CODE_BLOCK; return pgParser::KEYWORD_CODE; }", 59},
	{ 14, "{ currentValue.Identifier = root->newIdentifier(text()); bracket_mode = MODE::CODE_BLOCK; return pgParser::KEYWORD_HEADER; }", 60},
	{ 15, "{ currentValue.Identifier = root->newIdentifier(text()); return pgParser::KEYWORD_ROOTTYPE; }", 62},
	{ 16, "{ currentValue.Identifier = root->newIdentifier(text()); return pgParser::KEYWORD_BASECLASS; }", 63},
	{ 17, "{ currentValue.Identifier = root->newIdentifier(text()); return pgParser::KEYWORD_BASETYPE; }", 64},
	{ 18, "{ currentValue.Identifier = root->newIdentifier(text()); return pgParser::KEYWORD_RETURNTYPE; }", 65},
	{ 19, "{ currentValue.Identifier = root->newIdentifier(text()); return pgParser::KEYWORD_UNION; }", 66},
	{ 20, "{ currentValue.Identifier = root->newIdentifier(text()); return pgParser::KEYWORD_NONASSOC; }", 68},
	{ 21, "{ currentValue.Identifier = root->newIdentifier(text()); return pgParser::KEYWORD_LEFT; }", 69},
	{ 22, "{ currentValue.Identifier = root->newIdentifier(text()); return pgParser::KEYWORD_RIGHT; }", 70},
	{ 23, "{ currentValue.Identifier = root->newIdentifier(text()); return pgParser::OPERATOR_EPSILON; }", 72},
	{ 24, "{ return pgParser::OPERATOR_COLON; }", 74},
	{ 25, "{\n\t\t\t\t\t\t\t\t\t\tcurrentValue.Identifier = root->newIdentifier(text());\n\t\t\t\t\t\t\t\t\t\treturn pgParser::IDENTIFIER;\n\t\t\t\t\t\t\t\t\t}", 76},
	{ 26, "{ push(Context::LEX_STRING_LITERAL); stringLiteral = \"\"; return IGNORE; }", 80},
	{ 27, "{ return pgParser::OPERATOR_DOLLAR; }", 82},
	{ 28, "{ return pgParser::OPERATOR_EQUALS; }", 83},
	{ 29, "{ return pgParser::OPERATOR_OR; }", 84},
	{ 30, "{ return pgParser::OPERATOR_COLON; }", 85},
	{ 31, "{ return pgParser::OPERATOR_SEMICOLON; }", 86},
	{ 32, "{\n\t\t\t\t\t\t\t\t\t\tcurrentValue.Identifier = root->newIdentifier(text());\n\t\t\t\t\t\t\t\t\t\treturn pgParser::IDENTIFIER;\n\t\t\t\t\t\t\t\t\t }", 88},
	{ 33, "{ push(Context::LEX_STRING_LITERAL); stringLiteral = \"\"; return IGNORE; }", 93},
	{ 34, "{\n\t\t\t\t\t\t\tif (bracket_mode == MODE::NORMAL) {\n\t\t\t\t\t\t\t\tpush(Context::ACTION);\n\t\t\t\t\t\t\t\tyyfnln = getLineNumber();\n\t\t\t\t\t\t\t\tcurley_braces = 1;\n\t\t\t\t\t\t\t\taction = *begin();\n\t\t\t\t\t\t\t\treturn IGNORE;\n\t\t\t\t\t\t\t}\n\t\t\t\t\t\t\telse\n\t\t\t\t\t\t\t{\n\t\t\t\t\t\t\t\tpush(Context::CODE);\n\t\t\t\t\t\t\t\tyyfnln = getLineNumber();\n\t\t\t\t\t\t\t\tcurley_braces = 1;\n\t\t\t\t\t\t\t\taction = \"\";\n\t\t\t\t\t\t\t\tbracket_mode = MODE::NORMAL;\n\t\t\t\t\t\t\t\treturn IGNORE;\n\t\t\t\t\t\t\t}\n\t\t\t\t\t\t}", 95},
	{ 35, "{ bracket_mode = MODE::NORMAL; pop(); return pgParser::OPERATOR_CLOSE_CURLY_BRACE;}", 114},
	{ 36, "{ push(Context::COMMENT); return IGNORE; }", 116},
	{ 37, "{ push(Context::SINGLE_LINE_COMMENT); return IGNORE; }", 117},
	{ 38, "{ return IGNORE; }", 119},
	{ 39, "{ newLine(); return IGNORE; }", 120},
	{ 40, "{ std::cout << \"Invalid chararcter '\" << toString(*begin()) << \"'\\\n\"; return IGNORE; }", 121},
	{ 41, "{\n\t\t\t\t\t\t\t\t\t\tcurrentValue.StringLiteral = root->newStringLiteral(stringLiteral);\n\t\t\t\t\t\t\t\t\t\tpop();\n\t\t\t\t\t\t\t\t\t\treturn pgParser::STRING_LITERAL;\n\t\t\t\t\t\t\t\t\t}", 125},
	{ 42, "{\n\t\t\t\t\t\t\t\t\t\tstringLiteral += *begin();\n\t\t\t\t\t\t\t\t\t\treturn IGNORE;\n\t\t\t\t\t\t\t\t\t}", 130},
	{ 43, "{ action += *begin(); ++curley_braces; return IGNORE; }", 137},
	{ 44, "{\n                    \t\t\t\t\t\t\t\t\taction += \"}\";\n                    \t\t\t\t\t\t\t\t\tif (--curley_braces == 0) {\n                    \t\t\t\t\t\t\t\t\t\tpop();\n                    \t\t\t\t\t\t\t\t\t\tcurrentValue.Action = root->addAction(action, yyfnln);\n                    \t\t\t\t\t\t\t\t\t\treturn pgParser::TOKEN_ACTION;\n                    \t\t\t\t\t\t\t\t\t}\n                    \t\t\t\t\t\t\t\t\treturn IGNORE;\n                    \t\t\t\t\t\t\t\t}", 138},
	{ 45, "{ push(ACTION_DOUBLE_QUOTED_STRING); action += \"\\\"\"; return IGNORE; }", 147},
	{ 46, "{\n\t\t\t\t\t\t\t\t\t\t\t\t\t  for (auto i = begin(); i != end(); ++i)\n\t\t\t\t\t\t\t\t\t\t\t\t\t\taction += *i;\n\t\t\t\t\t\t\t\t\t\t\t\t\t  return IGNORE;\n\t\t\t\t\t\t\t\t\t\t\t\t\t}", 148},
	{ 47, "{\n\t\t\t\t\t\t\t\t\t\t\t\t\t  for (auto i = begin(); i != end(); ++i)\n\t\t\t\t\t\t\t\t\t\t\t\t\t\taction += *i;\n\t\t\t\t\t\t\t\t\t\t\t\t\t  return IGNORE;\n\t\t\t\t\t\t\t\t\t\t\t\t\t}", 153},
	{ 48, "{\n\t\t\t\t\t\t\t\t\t\t\t\t\t  newLine();\n\t\t\t\t\t\t\t\t\t\t\t\t\t  action += '\\n';\n\t\t\t\t\t\t\t\t\t\t\t\t\t  return IGNORE;\n\t\t\t\t\t\t\t\t\t\t\t\t\t}", 158},
	{ 49, "{ action += *begin(); return IGNORE; }", 163},
	{ 50, "{ action += _begin[0]; ++curley_braces; return IGNORE; }", 167},
	{ 51, "{\n                    \t\t\t\t\t\t\t\t\tif (--curley_braces == 0) {\n                    \t\t\t\t\t\t\t\t\t\tpop();\n                    \t\t\t\t\t\t\t\t\t\tcurrentValue.CodeBlock = new CodeBlock(action.c_str(), yyfnln, filename);\n                    \t\t\t\t\t\t\t\t\t\treturn pgParser::TOKEN_CODE;\n                    \t\t\t\t\t\t\t\t\t}\n\t\t\t\t\t\t\t\t\t\t\t\t\t\telse {\n\t                    \t\t\t\t\t\t\t\t\taction += \"}\";\n\t\t                \t\t\t\t\t\t\t\t\treturn IGNORE;\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t}\n                    \t\t\t\t\t\t\t\t}", 168},
	{ 52, "{ push(ACTION_DOUBLE_QUOTED_STRING); action += \"\\\"\"; return IGNORE; }", 179},
	{ 53, "{\n\t\t\t\t\t\t\t\t\t\t\t\t\t  for (auto i = begin(); i != end(); ++i)\n\t\t\t\t\t\t\t\t\t\t\t\t\t\taction += *i;\n\t\t\t\t\t\t\t\t\t\t\t\t\t  return IGNORE;\n\t\t\t\t\t\t\t\t\t\t\t\t\t}", 180},
	{ 54, "{\n\t\t\t\t\t\t\t\t\t\t\t\t\t  for (auto i = begin(); i != end(); ++i)\n\t\t\t\t\t\t\t\t\t\t\t\t\t\taction += *i;\n\t\t\t\t\t\t\t\t\t\t\t\t\t  return IGNORE;\n\t\t\t\t\t\t\t\t\t\t\t\t\t}", 185},
	{ 55, "{\n\t\t\t\t\t\t\t\t\t\t\t\t\t  newLine();\n\t\t\t\t\t\t\t\t\t\t\t\t\t  action += '\\n';\n\t\t\t\t\t\t\t\t\t\t\t\t\t  return IGNORE;\n\t\t\t\t\t\t\t\t\t\t\t\t\t}", 190},
	{ 56, "{ action += *begin(); return IGNORE; }", 195},
	{ 57, "{ action += *begin(); pop(); return IGNORE; }", 199},
	{ 58, "{ action += *begin(); push(ACTION_DOUBLE_QUOTED_STRING_ESCAPE_SEQUENCE); return IGNORE; }", 200},
	{ 59, "{ action += *begin(); return IGNORE; }", 201},
	{ 60, "{\n\t\t\t\t\t\t\t\t\t  for (auto i = begin(); i != end(); ++i)\n\t\t\t\t\t\t\t\t\t\taction += *i;\n\t\t\t\t\t\t\t\t\t  pop();\n\t\t\t\t\t\t\t\t\t  return IGNORE;\n\t\t\t\t\t\t\t\t\t}", 205},
	{ 61, "{\n\t\t\t\t\t\t\t\t\t  for (auto i = begin(); i != end(); ++i)\n\t\t\t\t\t\t\t\t\t\taction += *i;\n\t\t\t\t\t\t\t\t\t  pop();\n\t\t\t\t\t\t\t\t\t  return IGNORE;\n\t\t\t\t\t\t\t\t\t}", 211},
	{ 62, "{ action += *begin(); pop(); return IGNORE; }", 217},
	{ 63, "{ action += *begin(); pop(); return IGNORE; }", 218},
	{ 64, "{ action += *begin(); pop(); return IGNORE; }", 219},
	{ 65, "{ action += *begin(); pop(); return IGNORE; }", 220},
	{ 66, "{ action += *begin(); pop(); return IGNORE; }", 221},
	{ 67, "{ action += *begin(); pop(); return IGNORE; }", 222},
	{ 68, "{ action += *begin(); pop(); return IGNORE; }", 223},
	{ 69, "{ action += *begin(); pop(); return IGNORE; }", 224},
	{ 70, "{ action += *begin(); pop(); return IGNORE; }", 225},
	{ 71, "{ action += *begin(); pop(); return IGNORE; }", 226},
	{ 72, "{ action += *begin(); pop(); return IGNORE; }", 227},
	{ 73, "{\n    \t                                std::cerr << \"Invalid escape sequence '\\\\\" << _begin[0]\n    \t                                          << \"' in quoted string on line \" << getLineNumber() << std::endl;\n\t\t\t\t\t\t\t\t\t\taction += *begin();\n\t\t\t\t\t\t\t\t\t\tpop();\n    \t                                return ERROR;\n    \t                            }", 228},
	{ 74, "{ pop(); return IGNORE; }", 237},
	{ 75, "{ newLine(); return IGNORE; }", 238},
	{ 76, "{ return IGNORE;}", 239},
	{ 77, "{ newLine(); pop(); return IGNORE; }", 242},
	{ 78, "{ return IGNORE; }", 243}
  }),
  "ContextFreeGrammar",
  "Lexer",
  "ValueType",
  "int",
  {
    { "\n\t\t#include <iostream>\n\t\t#include \"g/Grammar/ContextFreeGrammar.h\"\n\t\t#include \"g/CodeBlock.h\"\n\t\t#include \"g/Actions.h\"\n\t\t#include \"nonstd/Utils.h\"\n\t\t#include \"pg.pg.h\"\n\n//\t\textern Grammar*\tgrammar;\t// TODO: fold in and remove !!!\n\n\t\tenum MODE { NORMAL, CODE_BLOCK, PRODUCTIONS };\n\t", 9, "C:\\Users\\aaron\\Projects\\G\\latest\\G - saving 6\\src\\bootstrap\\self-bootstrap\\lg-bootstrap-pg\\pg.lg" }
  },
  {
    { "\n\t\tstd::string action;\n\t\tstd::string stringLiteral;\n\n\t\tint yyfnln;\n\t\tint curley_braces = 0;\n\t\tMODE bracket_mode = MODE::NORMAL;\n\t", 21, "C:\\Users\\aaron\\Projects\\G\\latest\\G - saving 6\\src\\bootstrap\\self-bootstrap\\lg-bootstrap-pg\\pg.lg" }
  }
);

// End C:\Users\aaron\Projects\G\latest\G - saving 6\src\bootstrap\self-bootstrap\lg-bootstrap-pg\pg.lexer.cpp
