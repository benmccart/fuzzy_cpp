#ifndef FUZZY_MAPPING_HPP
#define FUZZY_MAPPING_HPP

#include <numeric>

#include <fuzzy/algorithm.hpp>
#include <fuzzy/element.hpp>
#include <fuzzy/relation.hpp>
#include <fuzzy/set.hpp>
#include <fuzzy/traits.hpp>




namespace fuzzy
{
	/**
	* A mapping rule uses a relation to map a supplied fuzzy input to a mapped fuzzy output.  Abstractly it is a functional
	* mapping from the domain to the range of the related fuzzy relation.
	*/
	template <class V, class M, class Container = std::vector<fuzzy::basic_element<V, M>>, class Tnorm = fuzzy::minimum<M>, class Tconorm = fuzzy::maximum<M> >
	requires std::integral<V> && std::floating_point<M> && tnorm_type<Tnorm> && tconorm_type<Tconorm>
	class mapping_rule
	{
	public:
		using relation_type = relation<V, M, Container, Tnorm>;
		using set_type = typename relation_type::set_type;
		using element_type = typename set_type::element_type;

		mapping_rule() = delete;
		constexpr mapping_rule(relation_type);
		constexpr mapping_rule(relation_type, Tconorm tconorm);


		constexpr set_type map(set_type const&) const;
	private:

		relation_type rel_;
	};

	/** Deduction guide to help construct the mapping_rule without having to explicitly specify the Tnorm or container parameters explicity. */
	template <class V, class M, class Container = std::vector<basic_element<V, M>>, class Tnorm = fuzzy::minimum<M>, class Tconorm = fuzzy::maximum<M>>
	mapping_rule(relation<V, M, Container, Tnorm> rel, Tconorm tconorm) -> mapping_rule<V, M, Container, Tnorm, Tconorm>;


	/**
	* Constructs a mapping rule using the provided relation.
	* @param rel The relation to use in generating the mapping rule.
	*/
	template <class V, class M, class Container, class Tnorm, class Tconorm>
	requires std::integral<V>&& std::floating_point<M>&& tnorm_type<Tnorm>&& tconorm_type<Tconorm>
	constexpr mapping_rule<V, M, Container, Tnorm, Tconorm>::mapping_rule(relation_type rel)
		: rel_(rel) 
	{
	}

	/**
	* Constructs a mapping rule using the provided relation.
	* @param rel The relation to use in generating the mapping rule.
	*/
	template <class V, class M, class Container, class Tnorm, class Tconorm>
	requires std::integral<V>&& std::floating_point<M>&& tnorm_type<Tnorm>&& tconorm_type<Tconorm>
	constexpr mapping_rule<V, M, Container, Tnorm, Tconorm>::mapping_rule(relation_type rel, Tconorm tconorm)
		: rel_(rel)
	{
	}

	/**
	* Maps the fuzzy input to a fuzzy output using the relation this mapping rule was constructed with.
	* @param variable The fuzzy input to map.
	* @return The mapped output.
	*/
	template <class V, class M, class Container, class Tnorm, class Tconorm>
	requires std::integral<V>&& std::floating_point<M>&& tnorm_type<Tnorm>&& tconorm_type<Tconorm>
	constexpr typename mapping_rule<V, M, Container, Tnorm, Tconorm>::set_type mapping_rule<V, M, Container, Tnorm, Tconorm>::map(set_type const &variable) const
	{
		using math::promote;
		using element_pair_t = std::pair<element_type, element_type>;

		// Check for special cases first.
		if (rel_.domain().empty())
			return set_type{};
		if (rel_.range().empty())
			return set_type{};
		if (variable.empty())
			return set_type{};

		if (variable.front().value() > rel_.domain().back() || variable.back() < rel_.domain().front())
			return set_type{};

		// Calculate the front/back domain values.
		set_type result;
		V const domain_first_v = std::max(rel_.domain().front().value(), variable.front().value());
		V const domain_last_v = std::min(rel_.domain().back().value(), variable.back().value());

		// Populate the set with variables calculated for domain as long as they are in range of [first,last].
		auto const delta_domain = promote(rel_.domain().back().value()) - promote(rel_.domain().front().value());
		V const range_first_v = promote(rel_.range().front().value());
		M const delta_range = static_cast<M>(promote(rel_.range().back().value()) - promote(range_first_v));
		set_type mapped_range_values;
		for (element_type e : variable)
		{
			if (e.value() < domain_first_v || domain_last_v < e.value())
				continue;

			auto const delta = promote(e.value()) - promote(rel_.domain().front().value());
			M const ratio = static_cast<M>(delta) / static_cast<M>(delta_domain);
			V const offset = static_cast<V>(std::round(ratio* delta_range));
			V const value = range_first_v + offset;
			mapped_range_values.insert(element_type{ value, static_cast<M>(0.0)});
		}

		// Find the first/last domain iterator.
		fuzzy::detail::set_operation_value_sequence domain_seq{ variable, rel_.domain() };
		auto itr_domain_beg = std::find_if(domain_seq.begin(), domain_seq.end(), [=](element_pair_t pair) { return pair.first.value() >= domain_first_v; });
		auto itr_domain_end = std::find_if(itr_domain_beg, domain_seq.end(), [=](element_pair_t pair) { return pair.first.value() > domain_last_v; });

		// FUTURE: Consider using cache for domain_intersection?  Or would that not actually be faster?

		// Iterate the range, calculate Tconom 'sum' for every pass of the domain.
		fuzzy::detail::set_operation_value_sequence range_seq{ mapped_range_values, rel_.range() };
		for (element_pair_t range_v : range_seq)
		{
			M const m = std::accumulate(itr_domain_beg, itr_domain_end, static_cast<M>(0.0), [&](M sum, element_pair_t pair)
			{
				
				M const domain_intersection = Tnorm::apply(pair.first.membership(), pair.second.membership());
				M const cartesian_product = rel_.membership(pair.first.value(), range_v.first.value());
				M const pairwise_product = Tnorm::apply(domain_intersection, cartesian_product);
				return Tconorm::apply(sum, pairwise_product);
			});

			result.insert(element_type{ range_v.first.value(), m });
		}
		detail::trim::apply(result);

		return result;
	}

}





#endif // FUZZY_MAPPING_HPP