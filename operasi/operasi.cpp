#include <eosio/eosio.hpp>

using namespace eosio;

class [[eosio::contract("operasi")]] operasi : public eosio::contract {
  public:
  
  operasi(name receiver, name code, datastream<const char*> ds):contract(receiver, code, ds) {}
	
  [[eosio::action]]
  void input( name user, uint64_t bil1, uint64_t bil2) {
  require_auth( user );

  catatan_input input_table(get_self(), get_first_receiver().value);
  auto iterator = input_table.find(user.value);
  if( iterator == input_table.end() )
  {
      input_table.emplace(user, [&] ( auto& row ) {
      row.user = user;
      row.bil1 = bil1;
      row.bil2 = bil2;

    });

  } else {
      input_table.modify(iterator, user, [&] ( auto& row ) {
      row.user = user;
      row.bil1 = bil1;
      row.bil2 = bil2;
    });
  }
}

  private:
  struct [[eosio::table]] input_row {
  name user;
  uint64_t bil1;
  uint64_t bil2;

  auto primary_key() const { return user.value; }
  };

  typedef eosio::multi_index<"input"_n, input_row> catatan_input;
};
